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
        MESSAGE_CONTROL_CHUNK,
    };
    enum enMessageCtrlTypeID
    {
        MESSAGE_CONTROL_TYPE_1 = 1,// set chunk size
        MESSAGE_CONTROL_TYPE_2 = 2,// abort message
        MESSAGE_CONTROL_TYPE_3 = 3,// acknowledgement
        MESSAGE_CONTROL_TYPE_5 = 5,// window acknowledgement size
        MESSAGE_CONTROL_TYPE_6 = 6,// set peer bandwith
    };
    class rtmp_chunk
    {
        enum chunk_state
        {
            ZEARO_CHUNK     = 0,
            FIRST_CHUNK     = 1,
            SECOND_CHUNK    = 2,
            THIRD_CHUNK     = 3
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
        long AssembleDataHeader(std::string& msg,chunk_state state, enChunkDataType ChunkType,enMessageCtrlTypeID msgCtrlTypeID,long MsgStreamID,long timeStamp = 0);
    public:
        std::vector<std::string> AssembleOneDataChunk(std::string pMsg, enChunkDataType chunkType,enMessageCtrlTypeID msgCtrlTypeID,long MsgStreamID,long timeStamp = 0);
        std::vector<std::string> AssembleOneControlChunk(enMessageCtrlTypeID msgCtrlTypeID,long MsgStreamID,long acknowledgementSize = 0, char limitType = 0);
        void DecodeOndeDataChunk(std::string pMsg);
    };
};

#endif
