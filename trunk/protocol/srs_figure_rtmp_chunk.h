//this is rtmp chunk decoder
#ifndef __HEADER_RTMP_CHUNK__
#define __HEADER_RTMP_CHUNK__

#include "../core/srs_figure_core.h"
#include <vector>
using namespace std;

namespace srs_rtmp_chunk
{
	class rtmp_chunk
	{
	public:
		rtmp_chunk(unsigned long lChunkStreamID,unsigned char cMessageType);
		virtual ~rtmp_chunk();
	private:
		unsigned long mMessageStreamID;
		unsigned char mMessageStreamType;
		unsigned long mChunkStreamID;

		std::vector<std::string> mChunkList;
	public:
		std::vector<std::string> AssembleOneChunk();
	};
};

#endif
