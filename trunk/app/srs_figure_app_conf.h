// this srs figure configure part
#ifndef __HEADER_APP_CONF__
#define __HEADER_APP_CONF__

#include "../core/srs_figure_core.h"
using namespace std;
#define DEFAULT_CONFIGURE_FILE "../conf/srs-figure.json"
class srs_figure_conf
{
public:
	srs_figure_conf();
	virtual ~srs_figure_conf();
public:
	static srs_figure_conf* pInstance;
	static srs_figure_conf* getInstance();
private:
	std::string mConfigureFilePath;
public:
	void setConfigureFile(const char*);
	void parse_file(const char* pConfigureFilePath);
};
#endif 
