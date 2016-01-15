//this is rtmp chunk decoder
#ifndef __HEADER_RTMP_CHUNK__
#define __HEADER_RTMP_CHUNK__

#include "../core/srs_figure_core.h"
#include <vector>
using namespace std;
// we just send c0 and c3 which is following the SRS's rules
// we need to decode c0 c1 c2 c3 chunk header and get the fect whether the server is SRS
namespace srs_rtmp_chunk
{
	enum enChunkDataType
	{
		AUDIO_DATA_CHUNK = 0,
		VIDEO_DATA_CHUNK,
	};
	class rtmp_chunk
	{
		enum chunk_state
		{
			UnInitialized = 0,
			FirstChunk = 1,
			SecondChunk=2,
			OtherChunk=3
		};
		enum basic_header_type
		{
			basic_header_type0 = 0,//2-63
			basic_header_type1,// 64-319
			basic_header_type2,// 64-65599
			basic_header_error,
		};
	public:
		rtmp_chunk(unsigned long lChunkStreamID,unsigned char cMessageType,long lTimeStamp);
		virtual ~rtmp_chunk();
	private:
		chunk_state mChunkState;
		basic_header_type mChunkBasicHeader;
		char* mpBasicHeader;
		unsigned long mTimeStamp;

		unsigned long mMessageStreamID;
		unsigned char mMessageStreamType;
		unsigned long mChunkStreamID;
		unsigned long max_chunk_data_size;
		
		std::vector<std::string> mChunkList;
		std::vector<std::string> mControlChunkList;
	protected:
		long AssembleHeader(std::string& msg, enChunkDataType ChunkType,long timeStamp = 0);
	public:
		std::vector<std::string> AssembleOneDataChunk(std::string pMsg, enChunkDataType ChunkType,long timeStamp = 0);
		std::vector<std::string> AssembleOneControlChunk(std::string pMsg);
	};
};

#endif
