#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include "event.h"

namespace seneca {
    class Logger {
        Event* m_events;
        size_t m_count;
        size_t m_capacity;
        
    public:
        Logger();
        ~Logger();
        
        // Disable copy operations
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        
        // Move operations
        Logger(Logger&& other) noexcept;
        Logger& operator=(Logger&& other) noexcept;
        
        void addEvent(const Event& event);
        
        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);
    };
}

#endif