#include "srs_figure_app_conf.h"

srs_figure_conf* srs_figure_conf::pInstance = nullptr;

srs_figure_conf* srs_figure_conf::getInstance()
{
	if(pInstance == nullptr) pInstance = new srs_figure_conf();
	return pInstance;
}

srs_figure_conf::srs_figure_conf() :
	mConfigureFilePath(DEFAULT_CONFIGURE_FILE)
{
}

srs_figure_conf::~srs_figure_conf()
{
}
