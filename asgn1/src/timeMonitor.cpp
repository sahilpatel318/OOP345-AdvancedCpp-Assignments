// Name: Sahil Hareshbhai Patel
// Seneca Student ID: 173793225
// Seneca email: shpatel27@myseneca.ca
// Date of completion: 06/06/2025
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work has 
// not been shared with any other student or 3rd party content provider.

#include "timeMonitor.h"

namespace seneca {

    // Marks the beginning of an event.
    // Stores the name of the event and the exact starting time using steady_clock.
    void TimeMonitor::startEvent(const char* name) {
        m_event_name = name; // Save the event name
        m_start_time = std::chrono::steady_clock::now(); // Record the starting time
    }

    // Marks the end of an event and returns an Event object with the duration.
    Event TimeMonitor::stopEvent() {
        auto end_time = std::chrono::steady_clock::now(); // Get current time (end time)

        // Calculate the duration from start to end in nanoseconds
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - m_start_time);

        // Return a new Event with the stored name and calculated duration
        return Event(m_event_name.c_str(), duration);
    }

}
