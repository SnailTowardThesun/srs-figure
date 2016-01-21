#ifndef __HEADER_RTMP_PROTOCOL_HANDSHAKE__ 
#define __HEADER_RTMP_PROTOCOL_HANDSHAKE__
// this is for rtmp protocol
#include <sys/types.h>
#include "../core/srs_figure_core.h"
namespace srs_figure_handshake
{
	// rtmp c0 s0
	class c0s0
	{
	public:
		unsigned char msg;
	public:
		c0s0(){ msg = 0x03; }// the number is from the RTMP standard document
		virtual ~c0s0(){ };
	};

	class c1s1
	{
	private:
		// 4 bytes
		int32_t time;
		// 4 bytes
		int32_t zero;
		// 1528 bytes
		unsigned char random_data[1527];// 1528 is from the RTMP standerd document
		// msg
		std::string mPpayload;
	public:
		c1s1();
		virtual ~c1s1();
	public:
		std::string getMsg();
	};

	class c2s2
	{
	private: 	
		std::string mpPayload;
	public:
		c2s2();
		virtual ~c2s2();
		std::string getMsg(std::string c1,std::string s1);

	};
};

#endif
