#include "srs_figure_rtmp_chunk.h"
using namespace srs_rtmp_chunk;
rtmp_chunk::rtmp_chunk(unsigned long lChunkStreamID,unsigned char cMessageType):
		mMessageStreamID(0),
		mMessageStreamType(cMessageType),
		mChunkStreamID(lChunkStreamID)
{
	
}

rtmp_chunk::~rtmp_chunk()
{

}

std::vector<std::string> rtmp_chunk::AssembleOneChunk()
{
	mChunkList.clear();
	return mChunkList;
}
