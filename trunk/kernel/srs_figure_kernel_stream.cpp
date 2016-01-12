#include "srs_figure_kernel_stream.h"
#include "../app/srs_figure_app_log.h"

srs_stream::srs_stream():
	mpTRecvThread(0),
	mIsExited(false)
{

}

srs_stream::~srs_stream()
{
	if(mpTRecvThread != 0)
		CloseSRSConnection();

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
	c0s0 c0;
	mSocket.sendMsg((const char*)&c0.msg,1);

	// recv s0
	const char* s0 = nullptr;
	size_t length = 0;
	mSocket.recvMsg(s0,length);
	if(length != 0 &&s0[0] != 3) return RESULT_ERROR;
	
	// recv s1
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
	c2s2 c2;
	mSocket.sendMsg((const char*)&c2,sizeof(c2s2));

	// finish the handshake,then create the receive thread
	if(mpTRecvThread == 0)
	{
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		int ret = pthread_create(&mpTRecvThread,&attr,InitRecvThread,(void*)this);
		pthread_attr_destroy(&attr);
		if(ret != 0) srs_figure_log::getInstance()->log("Error","srs_stream","error to create receive thread,and the error num is %d",ret);
		mIsExited = false;
	}

	return RESULT_OK;
}

long srs_stream::CloseSRSConnection()
{
	if(mpTRecvThread == 0) return RESULT_OK;
	// send signal to stop the receive thread
	mIsExited = true;
	void* state = nullptr;
	pthread_join(&mpTRecvThread,&state);
	mpTRecvThread = 0;
	return RESULT_OK;
}

void* srs_stream::RecvThread()
{
	char pMsg[DEFAULT_CHUNK_SIZE];
	size_t receivedMsgLength = 0;
	do
	{
		memset(pMsg,0,DEFAULT_CHUNK_SIZE);
		if(mSocket.recvMsg(pMsg,receivedMsgLength))
		{
			DecodeOneChunk(static_cast<const char*>(pMsg),static_cast<const int>(receivedMsgLength));
		}
	}while(!mIsExited);
	pthread_exit(0);
	return nullptr;
}

void srs_stream::DecodeOneChunk(const char* pMsg,const int lMsgLength)
{
	if(lMsgLength < 0) return;
}
