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

std::vector<std::string> rtmp_chunk::AssembleOneDataChunk(std::string pMsg,enChunkDataType chunkType, long MsgStreamID,long timeStamp)
{
	mChunkList.clear();
	if(mChunkBasicHeader ==basic_header_error) return mChunkList;
	
	if(pMsg.size() > max_chunk_data_size)
	{
		int loopTimes = pMsg.size() / max_chunk_data_size;
		// the first package, we should set the message header as type 0
		std::string chunkPackage_0,chunkHeader_0;
		AssembleHeader(chunkHeader_0,THIRD_CHUNK,chunkType,MsgStreamID,timeStamp);
		if(chunkHeader_0.size() > 0)
		{
			chunkPackage_0 += chunkHeader_0;
			chunkPackage_0 += pMsg.substr(0,max_chunk_data_size-1);
			mChunkList.push_back(chunkPackage_0);
		}
		// middle package the message header is type 3
		int i = 1;
		for(i = 1; i < loopTimes; i++)// const size aka max_chunk_data_size
		{
			std::string chunkPackage,chunkHeader;
			AssembleHeader(chunkHeader,THIRD_CHUNK,chunkType,MsgStreamID,timeStamp);
			if(chunkHeader.size() > 0)
			{
				chunkPackage += chunkHeader;
				chunkPackage += pMsg.substr(i * max_chunk_data_size,(i+1) * max_chunk_data_size-1);
				mChunkList.push_back(chunkPackage);
			}
		}
		// the last package, the chunkdata size is not const and message header is type 3
		std::string chunkPackage,chunkHeader;
		AssembleHeader(chunkHeader,THIRD_CHUNK,chunkType,MsgStreamID,timeStamp);
		if(chunkHeader.size() > 0)
		{
			chunkPackage += chunkHeader;
			chunkPackage += pMsg.substr(i * max_chunk_data_size-1,pMsg.size());
			mChunkList.push_back(chunkPackage);
		}
	}
	else
	{
		// message header is type 0
		std::string chunkPackage,chunkHeader;
		AssembleHeader(chunkHeader,ZEARO_CHUNK,chunkType,timeStamp);
		if(chunkHeader.size() > 0)
		{
			chunkPackage += chunkHeader;
			chunkPackage += pMsg;
			mChunkList.push_back(chunkPackage);
		}
	}

	return mChunkList;
}

long rtmp_chunk::AssembleHeader(std::string& msg ,chunk_state chunkState,enChunkDataType ChunkType,long MsgStreamID,long timeStamp)
{
	char* pMessageHeader = nullptr;
	int msgSize = 0,timeForWrite = 0;
	char* p = nullptr;
	switch(chunkState)
	{
	case ZEARO_CHUNK:
		// FMT is 0
		mpBasicHeader[0] = mpBasicHeader[0] & 0x3F;
		pMessageHeader = new char[11];
		// write timestamp 3 bytes
		timeForWrite = timeStamp < 0xFFFFFF ? timeStamp:0xFFFFFF;
		p = (char*)&timeForWrite;
		pMessageHeader[0] = p[0];
		pMessageHeader[1] = p[1];
		pMessageHeader[2] = p[2];
		
		// write message length 3 bytes
		p = (char*)&msgSize;
		pMessageHeader[3] = p[0];
		pMessageHeader[4] = p[1];
		pMessageHeader[5] = p[2];

		//message type id, 1 bytes 
		pMessageHeader[6] = ChunkType == VIDEO_DATA_CHUNK ? 9 :(ChunkType == AUDIO_DATA_CHUNK ? 8 : 10);

		//message stream ID;
		p = (char*)MsgStreamID;
		pMessageHeader[7] = p[0];
		pMessageHeader[8] = p[1];
		pMessageHeader[9] = p[2];
		pMessageHeader[10] = p[3];
		break;

	case FIRST_CHUNK:
		// FMT is 1
		mpBasicHeader[0] = (mpBasicHeader[0] & 0x3F) | 0x80;
		pMessageHeader = new char[3];
		break;

	case SECOND_CHUNK:
		// FMT is 2
		mpBasicHeader[0] = (mpBasicHeader[0] & 0x3F) | 0xC0;
		break;

	case THIRD_CHUNK:
		// FMT is 3
		mpBasicHeader[0] = (mpBasicHeader[0] & 0x3F) | 0xF0;
		break;
	}
	//make up the chunk header
	msg += mpBasicHeader;
	msg += pMessageHeader;
	
	// judge for extern timestamp
	//
	
	if(pMessageHeader != nullptr) delete[] pMessageHeader;
	return RESULT_OK;
}
