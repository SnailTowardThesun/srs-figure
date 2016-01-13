// this is amf part
//
#ifndef __HEADER_RTMP_AMF__
#define __HEADER_RTMP_AMF__
#include "../core/srs_figure_core.h"

using namespace std;

namespace srs_figure_amf
{
	class rtmp_chunk_header_basic_header_1
	{
	public:
		rtmp_chunk_header_basic_header_1();
		virtual rtmp_chunk_header_basic_header_1();
	public:
		unsigned char mcBasic;
	};

	class rtmp_chunk_header_basic_header_2
	{
	public:
		rtmp_chunk_header_basic_header_2();
		virtual ~rtmp_chunk_header_basic_header_2();
	public:
		unsigned char mcBasic[2];
	};

	class rtmp_chunk_header_basic_header_3
	{
	public:
		rtmp_chunk_header_basic_header_3();
		virtual ~rtmp_chunk_header_basic_header_3();
	public:
		unsigned char mcBasic[3];
	};

	class rtmp_chunk_header_message_header_type_0
	{
	public:
		rtmp_chunk_header_message_header_type_0();
		virtual rtmp_chunk_header_message_header_type_0();
	public:
		unsigned char mpMessage[11];
	};

	class rtmp_chunk_header_message_header_type_1
	{
	public:
		rtmp_chunk_header_message_header_type_1();
		virtual ~rtmp_chunk_header_message_header_type_1();
	public:
		unsigned char mpMessage[7];
	};

	class rtmp_chunk_header_message_header_type_2
	{
	public:
		rtmp_chunk_header_message_header_type_2();
		virtual ~rtmp_chunk_header_message_header_type_2();
	public:
		unsigned char mpMessage[3];
	};

	class rtmp_chunk_header_message_header_type_3
	{
	public:
		rtmp_chunk_header_message_header_type_3();
		virtual ~rtmp_chunk_header_message_header_type_3();
	};

	class rtmp_chunk_header_extend_timestamp
	{
	public:
		rtmp_chunk_header_extend_timestamp();
		virtual ~rtmp_chunk_header_extend_timestamp();
	public:
		int32_t mTimeStamp;
	};

	class rtmp_chunk_header
	{
	public:
		rtmp_chunk_header();
		virtual ~rtmp_chunk_header();
	public:
		void* mpBasic;
		void* mpMessage;
		void* mpTimestamp;
	};

	class rtmp_chunk
	{
	public:
		rtmp_chunk();
		virtual ~rtmp_chunk();
	public:
		rtmp_chunk_header mChunkHeader;
		unsigned char mpChunkData[DEFAULT_CHUNK_SIZE];
	};
};

#endif
