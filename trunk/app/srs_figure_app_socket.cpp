#include "srs_figure_app_socket.h"
#include "srs_figure_app_log.h"
using namespace srs_figure_socket;

#define MESSAGE_MAX_LENGTH 60*1024
#define SOCKET_TIME_OUT 1000

// base part 
base_socket::base_socket():mSocket(-1),
		mSockTimeOut(SOCKET_TIME_OUT),
		mpMsg(nullptr)
{
	memset(&mSocketAddr,0,sizeof(mSocketAddr));
	mpMsg = new char[MESSAGE_MAX_LENGTH];
}

base_socket::~base_socket()
{
	if(mpMsg != nullptr) delete mpMsg;
}
// tcp part
tcp_socket::tcp_socket()
{

}

tcp_socket::~tcp_socket()
{
	if(mSocket != -1) close(mSocket);
}


long tcp_socket::createSocket(const char* pTargetIP, const int sTargetPort)
{
	mSocket = socket(AF_INET,SOCK_STREAM,0);
	if(mSocket == -1)
	{
		srs_figure_log::getInstance()->log("Error",nullptr,"fail to create a TCP socket");
		return RESULT_ERROR;
	}
	
	mSocketAddr.sin_family = AF_INET;
	mSocketAddr.sin_port = htons(sTargetPort);
	mSocketAddr.sin_addr.s_addr = inet_addr(pTargetIP);

	setsockopt(mSocket,SOL_SOCKET,SO_RCVTIMEO,(char*)&mSockTimeOut,sizeof(long));

	// connect to server
	if(connect(mSocket,(const sockaddr*)&mSocketAddr,sizeof(mSocketAddr)) != 0)
	{
		srs_figure_log::getInstance()->log("Error",nullptr,"fail to connect to the server : %s ",pTargetIP);
		return RESULT_ERROR;
	}

	return RESULT_OK;
}

long tcp_socket::closeConnection()
{
	if(mSocket == -1) return RESULT_OK;
	close(mSocket);
	return RESULT_OK;
}

long tcp_socket::sendMsg(const char* pMsg,size_t msgLength)
{
	if(mSocket == -1) return RESULT_ERROR;
	int ret = send(mSocket,pMsg,msgLength,0);
	if(ret > 0)
	{
		return RESULT_OK;
	}
	return RESULT_ERROR;
}

long tcp_socket::recvMsg(std::string& pMsg, size_t& msgLength)
{
	if(mSocket == -1) return RESULT_ERROR;
	memset(mpMsg,0,MESSAGE_MAX_LENGTH);
	msgLength = recv(mSocket,mpMsg,MESSAGE_MAX_LENGTH,0);
	if(msgLength > 0)
	{
		pMsg =  mpMsg;
		return RESULT_OK;
	}
	return RESULT_ERROR;
}


//udp part
udp_socket::udp_socket()
{
}

udp_socket::~udp_socket()
{
}

long udp_socket::createSocket(const char* pTargetIP, const int sTargetPort)
{
	mSocket = socket(AF_INET,SOCK_DGRAM,0);
	if(mSocket == -1)
	{
		return RESULT_ERROR;
	}
	
	mSocketAddr.sin_family = AF_INET;
	mSocketAddr.sin_port = htons(sTargetPort);
	mSocketAddr.sin_addr.s_addr = inet_addr(pTargetIP);

	// connect to server
	if(connect(mSocket,(const sockaddr*)&mSocketAddr,sizeof(mSocketAddr)) != 0)
	{
		return RESULT_ERROR;
	}
	return RESULT_OK;
}
