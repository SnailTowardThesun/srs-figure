//
//
#ifndef SRS_FIGURE_APP_ST_THREAD_HEADER
#define SRS_FIGURE_APP_ST_THREAD_HEADER

#include <st.h>
#include <srs_figure_core.h>

namespace SrsFiThread
{
    class SrsFiStThread
    {
        typedef struct {
            void* pThis;
            void* pParam;
        }arg;
    public:
        SrsFiStThread();
        virtual ~SrsFiStThread();
    private:
        std::vector<st_thread_t> tid_list;
    public:
        virtual long start(void* pParam);
        virtual long stop();
        virtual long thread_func(void* arg);
    protected:
        static void* thread_cycle(void* arg);
    };
};
#endif
