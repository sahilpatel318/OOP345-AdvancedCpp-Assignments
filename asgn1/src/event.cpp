// Name: Sahil Hareshbhai Patel
// Seneca Student ID: 173793225
// Seneca email: shpatel27@myseneca.ca
// Date of completion: 06/06/2025
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work has 
// not been shared with any other student or 3rd party content provider.

#include "event.h"     // Our Event class definition
#include "settings.h"  // Contains the global time unit setting
#include <iomanip>     // Used for output formatting (setw, setprecision, etc.)

namespace seneca {

    // Default constructor - initializes with an empty name and 0 duration
    Event::Event() : m_name(""), m_duration(std::chrono::nanoseconds(0)) {}

    // Constructor with parameters - sets the name and duration of the event
    Event::Event(const char* name, const std::chrono::nanoseconds& duration)
        : m_name(name), m_duration(duration) {}

    // Overloaded << operator so we can easily print an Event with std::cout
    std::ostream& operator<<(std::ostream& os, const Event& event) {
        static int counter = 0; // Keeps count of how many events we’ve printed
        counter++;

        double duration_value = 0;   // Will hold the converted duration value
        int field_width = 11;        // Width for the printed duration (depends on unit)

        // Convert duration based on what time unit the user wants
        if (g_settings.m_time_units == "seconds") {
            duration_value = std::chrono::duration<double>(event.m_duration).count();
            field_width = 2; // Keep it small for seconds
        }
        else if (g_settings.m_time_units == "milliseconds") {
            duration_value = std::chrono::duration<double, std::milli>(event.m_duration).count();
            field_width = 5;
        }
        else if (g_settings.m_time_units == "microseconds") {
            duration_value = std::chrono::duration<double, std::micro>(event.m_duration).count();
            field_width = 8;
        }
        else {
            // Assume nanoseconds by default
            duration_value = static_cast<double>(event.m_duration.count());
            field_width = 11;
        }

        // Print the event in a clean, formatted way
        os << std::setw(2) << std::right << counter << ":"              // Event number
            << std::setw(41) << std::right << event.m_name << " -> "    // Event name
            << std::setw(field_width) << std::right;                    // Reserve space for duration

        // For seconds, just show integer part (truncate decimals)
        if (g_settings.m_time_units == "seconds") {
            long long duration_int = static_cast<long long>(duration_value);
            os << duration_int;
        }
        else {
            // For everything else, no decimals (setprecision(0))
            os << std::fixed << std::setprecision(0) << duration_value;
        }

        // Finally, print the unit (e.g., "milliseconds")
        os << " " << g_settings.m_time_units;

        return os;
    }
}
