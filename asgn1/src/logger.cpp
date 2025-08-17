// Name: Sahil Hareshbhai Patel
// Seneca Student ID: 173793225
// Seneca email: shpatel27@myseneca.ca
// Date of completion: 06/06/2025
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work has 
// not been shared with any other student or 3rd party content provider.

#include "logger.h"

namespace seneca {

    // Default constructor - initializes the logger with no events
    Logger::Logger() : m_events(nullptr), m_count(0), m_capacity(0) {}

    // Destructor - frees dynamically allocated memory
    Logger::~Logger() {
        delete[] m_events;
    }

    // Move constructor - takes over the resources of another Logger object
    Logger::Logger(Logger&& other) noexcept
        : m_events(other.m_events), m_count(other.m_count), m_capacity(other.m_capacity) {
        // Null out the source logger's data so it doesn’t delete it later
        other.m_events = nullptr;
        other.m_count = 0;
        other.m_capacity = 0;
    }

    // Move assignment operator - handles assignment from an rvalue
    Logger& Logger::operator=(Logger&& other) noexcept {
        if (this != &other) {
            // Clean up current resources
            delete[] m_events;

            // Transfer ownership from the other object
            m_events = other.m_events;
            m_count = other.m_count;
            m_capacity = other.m_capacity;

            // Reset the source object
            other.m_events = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    // Adds a new event to the logger, resizing the array if needed
    void Logger::addEvent(const Event& event) {
        // If capacity is full, resize the array (double the size)
        if (m_count >= m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            Event* new_events = new Event[new_capacity];

            // Copy over existing events
            for (size_t i = 0; i < m_count; ++i) {
                new_events[i] = m_events[i];
            }

            // Replace old array
            delete[] m_events;
            m_events = new_events;
            m_capacity = new_capacity;
        }

        // Add the new event
        m_events[m_count++] = event;
    }

    // Overloaded output operator - prints all logged events to the stream
    std::ostream& operator<<(std::ostream& os, const Logger& logger) {
        for (size_t i = 0; i < logger.m_count; ++i) {
            os << logger.m_events[i] << std::endl;  // Each event uses its own << overload
        }
        return os;
    }

}
