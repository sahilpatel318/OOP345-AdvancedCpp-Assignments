#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include "event.h"
#include <chrono>
#include <string>

namespace seneca {
    class TimeMonitor {
        std::chrono::steady_clock::time_point m_start_time;
        std::string m_event_name;
        
    public:
        void startEvent(const char* name);
        Event stopEvent();
    };
}

#endif