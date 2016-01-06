//this is srs client used to connect to srs server.
//We can judge whether the web station is using srs server by analyse the data returned by web station

#ifndef __HEADER_SRSCLIENT_CLASS__
#define __HEADER_SRSCLIENT_CLASS__
#include "protocol/srs_figure_rtmp_handshake.h"
class SRSClient
{
public:
	SRSClient();
	virtual ~SRSClient();
};

#endif
