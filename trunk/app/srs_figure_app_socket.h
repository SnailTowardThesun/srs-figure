// this is srs-figure socket app
#ifndef __HEADER_SOCKET_APP__
#define __HEADER_SOCKET_APP__

#include "../core/srs_figure_core.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <csignal>
using namespace std;

namespace srs_figure_socket
{
	class base_socket
	{
	public:
		base_socket();
		virtual ~base_socket();
	public:
		virtual long createSocket(const char* pTargetIP,const int lTargetPort) = 0;
		virtual long sendMsg(const char* pMsg,size_t msgLength) = 0;
		virtual long recvMsg(const char* pMsg,size_t& msgLength) = 0;
	public:
		int mSocket;
		struct sockaddr_in mSocketAddr;
		char* mpMsg;
	};
	class tcp_socket: base_socket
	{
	public:
		tcp_socket();
		virtual ~tcp_socket();
	public:
		long createSocket(const char* pTargetIP,const int lTargetPort);
		long sendMsg(const char* pMsg, size_t msgLenght);	
		virtual long recvMsg(const char* pMsg,size_t& msgLength);

	};

	class udp_socket: base_socket
	{
	public:
		udp_socket();
		virtual ~udp_socket();
		long createSocket(const char* pTargetIP,const int lTargetPort);
	};
};

#endif
