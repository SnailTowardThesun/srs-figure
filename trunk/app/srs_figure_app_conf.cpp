#include "srs_figure_app_conf.h"
#include "srs_figure_app_log.h"
#include <errno.h>
srs_figure_conf* srs_figure_conf::pInstance = nullptr;

srs_figure_conf* srs_figure_conf::getInstance()
{
    if(pInstance == nullptr) pInstance = new srs_figure_conf();
    return pInstance;
}

srs_figure_conf::srs_figure_conf() :
    mConfigureFilePath(DEFAULT_CONFIGURE_FILE),
    mstrServerIP("127.0.0.1"),
    mlServerPort(1935)
{

}

srs_figure_conf::~srs_figure_conf()
{
}

void srs_figure_conf::setConfigureFile(const std::string fileName)
{
    mConfigureFilePath = fileName;
}

void srs_figure_conf::parse_file()
{   
    char ReadBuffer[JSON_READ_BUFFER_MAX_SIZE];
    Document jsonDoc;
    FILE* pfConfFilePointer = fopen(mConfigureFilePath.c_str(),"r");
    errno = 0;
    if(pfConfFilePointer == NULL)
    {
        srs_figure_log::getInstance()->log("Error","Error","fail to open file and the num is %d",errno);
        return;
    }

    FileReadStream fStream(pfConfFilePointer,(char*)ReadBuffer,sizeof(ReadBuffer));
    fclose(pfConfFilePointer);

    jsonDoc.Parse(ReadBuffer);
    
    // already get the information from the file,then get the value
    if(jsonDoc.HasMember("server_ip") && jsonDoc["server_ip"].IsString())
    {
        mstrServerIP = jsonDoc["server_ip"].GetString();
    }   
    cout<<mstrServerIP<<endl;

    if(jsonDoc.HasMember("server_port") && jsonDoc["server_port"].IsInt())
    {
        mlServerPort = jsonDoc["server_port"].GetInt();
    }
    cout<<mlServerPort<<endl;

    if(jsonDoc.HasMember("srs_figure_log_file") && jsonDoc["srs_figure_log_file"].IsString())
    {
        mstrLogFilePath = jsonDoc["srs_figure_log_file"].GetString();
        srs_figure_log::getInstance()->setLogFile(mstrLogFilePath);
        srs_figure_log::getInstance()->log("Info","log","set srs figure's log %s",mstrLogFilePath.c_str());
    }
    cout<<mstrLogFilePath<<endl;
}
