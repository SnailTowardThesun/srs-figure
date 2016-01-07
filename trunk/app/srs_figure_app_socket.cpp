#include "srs_figure_app_socket.h"
using namespace srs_figure_socket;
// base part 
base_socket::base_socket():mSocket(-1)
{
	memset(&mSocketAddr,0,sizeof(mSocketAddr));
}

base_socket::~base_socket()
{
}
// tcp part
tcp_socket::tcp_socket()
{

}

tcp_socket::~tcp_socket()
{

}

long tcp_socket::createSocket(const char* pTargetIP, const int sTargetPort)
{
	if(mSocket = socket(AF_INET,SOCK_STREAM,0) == -1)
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



//udp part
udp_socket::udp_socket()
{
}

udp_socket::~udp_socket()
{
}

long udp_socket::createSocket(const char* pTargetIP, const int sTargetPort)
{
	if(mSocket = socket(AF_INET,SOCK_DGRAM,0) == -1)
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
