#include "srs_figure_app_log.h"
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

srs_figure_log* srs_figure_log::pInstance = nullptr;
pthread_mutex_t srs_figure_log::mutex = PTHREAD_MUTEX_INITIALIZER;

srs_figure_log::srs_figure_log() : mLogFile(DEFAULT_SRS_FIGURE_LOG_FILE),
        log_data(nullptr),
        flogFile(-1)
{
    log_data = new char[LOG_MAX_SIZE];
}

srs_figure_log::~srs_figure_log()
{
    if(log_data != nullptr) delete log_data;
    if(flogFile > 0) ::close(flogFile);
}

srs_figure_log* srs_figure_log::getInstance()
{
    if(pInstance == nullptr)
            pInstance = new srs_figure_log();
    return pInstance;
}

void srs_figure_log::setLogFile(const std::string strLogFile)
{
    mLogFile = strLogFile;
}

bool srs_figure_log::generate_header(const char* tag, int context_id, const char* level_name, int* header_size)
{
    // clock time
    timeval tv;
    if (gettimeofday(&tv, NULL) == -1) 
    {
        return false;
    }
    
    // to calendar time
    struct tm* tm;
    
    if ((tm = localtime(&tv.tv_sec)) == NULL) 
    {
        return false;
    }
    
    // write log header
    int log_header_size = -1;
     
    if (tag) 
    {
        log_header_size = snprintf(log_data, LOG_MAX_SIZE, 
                "[%d-%02d-%02d %02d:%02d:%02d.%03d][%s][%s][%d][%d] ", 
                1900 + tm->tm_year, 1 + tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(tv.tv_usec / 1000), 
                level_name, tag, getpid(), context_id);
    } 
    else 
    {
        log_header_size = snprintf(log_data, LOG_MAX_SIZE, 
                "[%d-%02d-%02d %02d:%02d:%02d.%03d][%s][%d][%d] ", 
                1900 + tm->tm_year, 1 + tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(tv.tv_usec / 1000), 
                level_name, getpid(), context_id);
    }

    if (log_header_size == -1) 
    {
        return false;
    }
    
    // write the header size.
    *header_size = LOG_MAX_SIZE - 1 < log_header_size ? LOG_MAX_SIZE-1 : log_header_size;
    
    return true;

}

long srs_figure_log::log(const char* level_name, const char* tag ,const char *fmt, ...)
{
    pthread_mutex_lock(&mutex);
    int header_size = 0,size = 0;
    if(!generate_header(tag,0,level_name,&header_size))
    {
        pthread_mutex_unlock(&mutex);
        return RESULT_ERROR;
    }

    va_list ap;
    va_start(ap,fmt);
    
    size = header_size + vsnprintf(log_data + header_size ,LOG_MAX_SIZE - header_size,fmt,ap);
    va_end(ap);

    size = size > LOG_MAX_SIZE - 1 - 1 ? LOG_MAX_SIZE - 1 - 1 : size;

    flogFile = ::open(mLogFile.c_str(), O_RDWR | O_APPEND);
    
    if(flogFile == -1) {
        flogFile = ::open(mLogFile.c_str(), 
            O_RDWR | O_CREAT | O_TRUNC, 
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
        );
    }
    if(flogFile > 0)
    {
        ::write(flogFile,log_data,size);
        ::write(flogFile,"\n",1);
    }
    pthread_mutex_unlock(&mutex);
    return RESULT_OK;
}
