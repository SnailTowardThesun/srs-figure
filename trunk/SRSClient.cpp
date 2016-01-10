#include "SRSClient.h"
#include "./app/srs_figure_app_conf.h"
SRSClient::SRSClient()
{
	srs_figure_conf::getInstance()->parse_file();
}

SRSClient::~SRSClient()
{

}
