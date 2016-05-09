//
//
#include <srs_figure_app_st_thread.hpp>
#include <srs_figure_app_log.h>
using namespace SrsFiThread;

SrsFiStThread::SrsFiStThread()
{
}

SrsFiStThread::~SrsFiStThread()
{
    stop();
    tid_list.clear();
}

long SrsFiStThread::start(void* param)
{
    int ret = RESULT_OK;
    arg* pass_param = new arg();
    pass_param->pThis = this;
    pass_param->pParam = param;

    st_thread_t tid = NULL;
    if ((tid = st_thread_create(thread_cycle, (void*)pass_param, 0, 0)) == NULL) {
        ret = RESULT_ERROR;
        srs_figure_log::getInstance()->log("error", "", "create st thread failed");
        return ret;
    }
    tid_list.push_back(tid);
    return ret;
}

long SrsFiStThread::stop()
{
    int ret = RESULT_OK;
    std::vector<st_thread_t>::iterator it;
    for (it = tid_list.begin(); it != tid_list.end(); ++it) {
        st_thread_t tid = (*it);
        st_thread_interrupt(tid);
    }
    tid_list.clear();
    return ret;
}

long SrsFiStThread::thread_func(void* arg)
{
    int ret = RESULT_OK;
    srs_figure_log::getInstance()->log("trace", "", "step into the base st thread function");
    return ret;
}

void* SrsFiStThread::thread_cycle(void* param)
{
    arg* pArg = (arg*)param;
    SrsFiStThread* pthread = (SrsFiStThread*)pArg->pThis;
    pthread->thread_func(pArg->pParam);
    free(param);
    return NULL;
}
