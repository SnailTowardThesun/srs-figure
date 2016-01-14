#include "srs_figure_rtmp_chunk.h"
#include "../app/srs_figure_app_log.h"

using namespace srs_rtmp_chunk;
rtmp_chunk::rtmp_chunk(unsigned long lChunkStreamID,unsigned char cMessageType,long lTimeStamp):
		mChunkBasicHeader(basic_header_error),
		mpBasicHeader(nullptr),
		mTimeStamp(lTimeStamp),
		mMessageStreamID(0),
		mMessageStreamType(cMessageType),
		mChunkStreamID(lChunkStreamID),
		max_chunk_data_size(128)
{
	// format mpBasicHeader
	if(mChunkStreamID < 64)
	{
		mpBasicHeader = new char[1];
		mpBasicHeader[0] = mChunkStreamID;
	}
	else if(mChunkStreamID < 319)
	{
		mpBasicHeader = new char[2];
		mChunkBasicHeader = basic_header_type1;
		
		mpBasicHeader[0] = 0;
		mpBasicHeader[1] = mChunkStreamID - 64;
	}
	else if(mChunkStreamID <= 65599)
	{
		mpBasicHeader = new char[3];
		mChunkBasicHeader = basic_header_type2;

		mpBasicHeader[0] = 1;
		if(mChunkStreamID % 256 < 64)
		{
			mpBasicHeader[2] = mChunkStreamID / 256 - 1;
			mpBasicHeader[1] = mChunkStreamID - mpBasicHeader[2] * 256 - 64;
		}
		else
		{
			mpBasicHeader[2] = mChunkStreamID / 256;
			mpBasicHeader[1] = mChunkStreamID - mpBasicHeader[2] * 256 - 64;
		}
	}
	else
	{
		mChunkBasicHeader = basic_header_error;
		srs_figure_log::getInstance()->log("Error","rtmp chunk create","fail to initalize chunk header,the chunk stream ID %d is out of range",mChunkStreamID);
	}
}

rtmp_chunk::~rtmp_chunk()
{
	if(mpBasicHeader != nullptr) delete[] mpBasicHeader;
}

std::vector<std::string> rtmp_chunk::AssembleOneControlChunk(std::string pMsg)
{
	mControlChunkList.clear();
	

	return mControlChunkList;
}

std::vector<std::string> rtmp_chunk::AssembleOneDataChunk(std::string pMsg, enChunkDataType chunkType,long timeStamp)
{
	mChunkList.clear();
	if(mChunkBasicHeader ==basic_header_error) return mChunkList;
	
	if(pMsg.size() > max_chunk_data_size)
	{
		int loopTimes = pMsg.size() / max_chunk_data_size;
		int i = 0;
		for(i = 0; i < loopTimes; i++)// const size aka max_chunk_data_size
		{
			std::string chunkPackage,chunkHeader;
			AssembleHeader(chunkHeader,chunkType,timeStamp);
			if(chunkHeader.size() > 0)
			{
				chunkPackage += chunkHeader;
				chunkPackage += pMsg.substr(i * max_chunk_data_size,(i+1) * max_chunk_data_size);
				mChunkList.push_back(chunkPackage);
			}
		}
		// the last size of data
		std::string chunkPackage,chunkHeader;
		AssembleHeader(chunkHeader,chunkType,timeStamp);
		if(chunkHeader.size() > 0)
		{
			chunkPackage += chunkHeader;
			chunkPackage += pMsg.substr(i * max_chunk_data_size,pMsg.size());
			mChunkList.push_back(chunkPackage);
		}
	}
	else
	{
		std::string chunkPackage,chunkHeader;
		AssembleHeader(chunkHeader,chunkType,timeStamp);
		if(chunkHeader.size() > 0)
		{
			chunkPackage += chunkHeader;
			chunkPackage += pMsg;
			mChunkList.push_back(chunkPackage);
		}
	}

	return mChunkList;
}

long rtmp_chunk::AssembleHeader(std::string& msg ,enChunkDataType ChunkType,long timeStamp)
{
	char* pMessageHeader = nullptr;
	switch(mChunkState)
	{
	case UnInitialized:
		mChunkState = FirstChunk;
		// FMT is 0
		mpBasicHeader[0] = mpBasicHeader[0] & 0x3F;
		pMessageHeader = new char[11];
		break;

	case FirstChunk:
		mChunkState = SecondChunk;
		// FMT is 2
		mpBasicHeader[0] = (mpBasicHeader[0] & 0x3F) | 0x80;
		pMessageHeader = new char[3];
		break;

	case SecondChunk:
		mChunkState = OtherChunk;
		// FMT is 3
		mpBasicHeader[0] = (mpBasicHeader[0] & 0x3F) | 0xC0;
		break;

	default:
		break;
	}
	if(pMessageHeader != nullptr) delete[] pMessageHeader;
	return RESULT_OK;
}
