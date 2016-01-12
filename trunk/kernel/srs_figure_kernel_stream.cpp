#include "srs_figure_kernel_stream.h"

srs_stream::srs_stream()
{

}

srs_stream::~srs_stream()
{

}

// for rtmp handshake
long srs_stream::CreateSRSConnection()
{
	// create a socket
	//
	int ret = mSocket.createSocket(srs_figure_conf::getInstance()->getServerIP().c_str(),srs_figure_conf::getInstance()->getServerPort());
	if(ret != RESULT_OK)
	{
		return RESULT_ERROR;
	}
	// send c0
	//
		c0s0 c0;
		mSocket.sendMsg((const char*)&c0.msg,1);
	// recv s0
	//
		const char* s0 = nullptr;
		size_t length = 0;
		mSocket.recvMsg(s0,length);
		if(length != 0 &&s0[0] != 3) return RESULT_ERROR;
	// recv s1
	//
		const char* s1 = nullptr;
		length = 0;
		mSocket.recvMsg(s1,length);
		if(length == 0 || s1 == nullptr) return RESULT_ERROR;
	// send c1
		c1s1 c1;
		mSocket.sendMsg((const char*)&c1,sizeof(c1s1));
	// recv s2
		const char* s2 = nullptr;
		length = 0;
		mSocket.recvMsg(s2,length);
		if(length == 0 || s2 == nullptr) return RESULT_ERROR;
	// send c2
	return RESULT_OK;
}
