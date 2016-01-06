#ifndef __HEADER_RTMP_PROTOCOL_HANDSHAKE__ 
#define __HEADER_RTMP_PROTOCOL_HANDSHAKE__
// this is for rtmp protocol
#include <sys/types.h>

namespace _srs_figure_handshake
{
	// rtmp c0 s0
	class c0s0
	{
	public:
		unsigned char msg;
	public:
		c0s0(){ msg = 3; }// the number is from the RTMP standard document
		virtual ~c0s0();
	};

	class c1s1
	{
	public:
		// 4 bytes
		int32_t time;
		// 4 bytes
		int32_t zero;
		// 1528 bytes
		unsigned char random_data[1528];// 1528 is from the RTMP standerd document
	public:
		c1s1();
		virtual ~c1s1();
	};

	class c2s2
	{
	public: 
		// 4 bytes
		int32_t time;
		// 4 bytes
		int32_t zero;
		// 1528 bytes
		unsigned char random_echo[1528];// 1528 is from the RTMP standerd document

	public:
		c2s2();
		virtual ~c2s2();
	};
};

#endif
