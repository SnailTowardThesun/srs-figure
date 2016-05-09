#include "srs_figure_rtmp_handshake.h"
using namespace srs_figure_handshake;
c1s1::c1s1():time(0),zero(0),mPpayload("")
{
    memset(random_data,5,1528);
}

c1s1::~c1s1()
{
    
}

std::string c1s1::getMsg()
{
    time = ::time(NULL);
    char* tmp = nullptr;
    tmp = (char*)&time;
    mPpayload += tmp[0];
    mPpayload += tmp[1];
    mPpayload += tmp[2];
    mPpayload += tmp[3];

    tmp = (char*)&zero;
    mPpayload += tmp[0];
    mPpayload += tmp[1];
    mPpayload += tmp[2];
    mPpayload += tmp[3];

    mPpayload += (char*)random_data;

    return mPpayload;
}

c2s2::c2s2()
{
}

c2s2::~c2s2()
{
    
}

std::string c2s2::getMsg(std::string c0c1,std::string s0s1)
{
    mpPayload += s0s1[1];
    mpPayload += s0s1[2];
    mpPayload += s0s1[3];
    mpPayload += s0s1[4];

    mpPayload += c0c1[1];
    mpPayload += c0c1[2];
    mpPayload += c0c1[3];
    mpPayload += c0c1[4];

    mpPayload += (char*)&s0s1.c_str()[9];

    return mpPayload;
}
