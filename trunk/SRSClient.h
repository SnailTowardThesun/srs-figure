//this is srs client used to connect to srs server.
//We can judge whether the web station is using srs server by analyse the data returned by web station
#include <iostream>
using namespace std;
#include "protocol/rtmp.h"
class SRSClient
{
public:
	SRSClient();
	virtual ~SRSClient();
};
