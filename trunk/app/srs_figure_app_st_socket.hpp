// socket using st
//
#ifndef SRS_FIGURE_APP_ST_SOCKET_HEADER
#define SRS_FIGURE_APP_ST_SOCKET_HEADER

#include <srs_figure_core.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <csignal>
#include <st.h>
namespace srs_figure_st_socket
{
    class SrsFiStBaseSocket
    {
    public:
        SrsFiStBaseSocket() {};
        virtual ~SrsFiStBaseSocket() {};
    };

    class SrsFiTcpServerSocket : public SrsFiStBaseSocket
    {
    public:
        SrsFiTcpServerSocket();
        virtual ~SrsFiTcpServerSocket();
    private:
        st_netfd_t conn_fd;
        std::string ip_address;
        long ip_port;
    public:
        virtual long initialize(std::string ip, int port);
        virtual long sendMsg(const char* pMsg, size_t msgLength);
        virtual long recvMsg(char* strMsg, size_t msgLength);
        virtual long closeConnection();
    };
};

#endif
