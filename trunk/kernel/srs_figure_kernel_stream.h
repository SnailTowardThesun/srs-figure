// this srs figure kernel part
#ifndef __HEADER_KERNEL_STREAM__
#define __HEADER_KERNEL_STREAM__

#include "../core/srs_figure_core.h"
#include "../app/srs_figure_app_socket.h"
#include "../app/srs_figure_app_conf.h"
#include "../protocol/srs_figure_rtmp_handshake.h"
using namespace std;
using namespace srs_figure_socket;
using namespace srs_figure_handshake;
class srs_stream
{
public:
    srs_stream();
    ~srs_stream();
private:
    tcp_socket mSocket;
    pthread_t mpTRecvThread;
    bool mIsExited;
protected:
    static void* InitRecvThread(void* pParam){ return ((srs_stream*)pParam)->RecvThread(); }
    void* RecvThread();
    void DecodeOneChunk(const char* pMsg,const int lMsg);
public:
    long CreateSRSConnection();
    long CloseSRSConnection();
};

#endif
