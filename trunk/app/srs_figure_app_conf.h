// this srs figure configure part
#ifndef __HEADER_APP_CONF__
#define __HEADER_APP_CONF__

#include "../core/srs_figure_core.h"
#include <string>
using namespace std;
#include "../rapidjson/rapidjson.h" // for parser json configure
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/document.h"
using namespace rapidjson;
#define DEFAULT_CONFIGURE_FILE "./conf/srs-figure.json"
#define JSON_READ_BUFFER_MAX_SIZE 65536

#define DEFAULT_SERVER_IP "127.0.0.1"
#define DEFAULT_SERVER_PORT 1935

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

	std::string mstrServerIP;
	long mlServerPort;
	std::string mstrLogFilePath;
public:
	void setConfigureFile(const std::string fileName);
	void parse_file();

	std::string getServerIP() { return mstrServerIP; }
	long getServerPort(){ return mlServerPort; };
	std::string getLogFilePath(){ return mstrLogFilePath; }
};
#endif 
