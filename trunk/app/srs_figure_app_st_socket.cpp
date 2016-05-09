//
//
#include <srs_figure_app_st_socket.hpp>
#include <srs_figure_app_log.h>
using namespace srs_figure_st_socket;


static const long MAX_LENGTH_OF_QUEUE_TO_SOCKET = 1000;
#define TIME_OUT_LIMIT 1000000L * 30
SrsFiTcpServerSocket::SrsFiTcpServerSocket()
{
    conn_fd = NULL;
    ip_port = 0;
}

SrsFiTcpServerSocket::~SrsFiTcpServerSocket()
{
    closeConnection();
}

long SrsFiTcpServerSocket::initialize(std::string ip, int port)
{
    int ret = RESULT_OK;
    if (ip.empty()) {
        srs_figure_log::getInstance()->log("warning", "", "ip is empty, so chose a random port");
    }

    if (port < 2 || port > 65535) {
        srs_figure_log::getInstance()->log("warning", "", "the port is beyound limit");
        return RESULT_ERROR;
    }

    ip_address = ip;
    ip_port = port;

    // initialize the socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if ((ret = server_socket) == -1) {
        srs_figure_log::getInstance()->log("error", "", "create socket failed,ret=%d", ret);
        return ret;
    }
    // local ip
    struct sockaddr_in sockad;
    sockad.sin_family = AF_INET;
    sockad.sin_port = htons((uint16_t)ip_port);
    sockad.sin_addr.s_addr = htonl(INADDR_ANY);
    // bind socket
    if ((ret = bind(server_socket, (const sockaddr*)&sockad, sizeof(sockad))) < 0) {
        srs_figure_log::getInstance()->log("error", "", "bind the socket failed, ret=%d", ret);
        return ret;
    }
    // listen
    if ((ret = listen(server_socket, MAX_LENGTH_OF_QUEUE_TO_SOCKET)) < 0) {
        srs_figure_log::getInstance()->log("error", "", "listen socket failed, ret=%d", ret);
        return ret;
    }
    // st
    if ((conn_fd = st_netfd_open(server_socket)) == NULL) {
        srs_figure_log::getInstance()->log("error", "", "st open socket failed");
        return RESULT_ERROR;
    }
    if (st_netfd_serialize_accept(conn_fd)  < 0) {
        srs_figure_log::getInstance()->log("error", "", "accept socket failed");
        return RESULT_ERROR;
    }
    return ret;
}

long SrsFiTcpServerSocket::sendMsg(const char* pMsg, size_t msgLength)
{
    int ret = 0;
    if (pMsg == NULL || msgLength < 1) {
        srs_figure_log::getInstance()->log("trace", "", "the data to be sent is empty");
        return 0;
    }
    return st_write(conn_fd, pMsg, (int)msgLength, ST_UTIME_NO_TIMEOUT);
}

long SrsFiTcpServerSocket::recvMsg(char* pMsg, size_t msgLength)
{
    return st_read(conn_fd, pMsg, msgLength, TIME_OUT_LIMIT);
}

long SrsFiTcpServerSocket::closeConnection()
{
    if (conn_fd != NULL) {
        st_netfd_close(conn_fd);
        conn_fd = NULL;
    }
    return RESULT_OK;
}
