// this srs-figure log part
//
#ifndef __HEADER_APP_LOG__
#define __HEADER_APP_LOG__

#include "../core/srs_figure_core.h"
#include <iostream>
using namespace std;

#define DEFAULT_SRS_FIGURE_LOG_FILE "srs-figure.log"
#define LOG_MAX_SIZE 4096


class srs_figure_log
{
public:
	srs_figure_log();
	virtual ~srs_figure_log();
public:
	static srs_figure_log *pInstance;
	static srs_figure_log *getInstance();
	static pthread_mutex_t mutex;
private:
	std::string mLogFile;
	char* log_data;
	int flogFile;
protected:
	bool generate_header(const char* tag, int context_id, const char* level_name, int* header_size);

public:
	void setLogFile(const std::string strLogFile);
	long log(const char* level_name, const char* tag, const char *fmt,...);
};

#endif
