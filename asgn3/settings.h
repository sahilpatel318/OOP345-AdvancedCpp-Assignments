#pragma once
/*
 Name : SAHIL HARESHBHAI PATEL
 Email: shpatel27@myseneca.ca
 Student ID: 173793225
 Date: July 18, 2025

 I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
 This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca
{
    /*
     * The Settings struct holds configuration options
     * used by the application to control formatting and display behavior.
     */
    struct Settings
    {
        short m_maxSummaryWidth{80};  // Maximum width for summary text output (default: 80 characters)
        bool m_tableView{false};      // If true, enables table-style output format
    };

    /*
     * Global instance of Settings used throughout the application.
     * Defined in settings.cpp and declared as extern here to allow shared access.
     */
    extern Settings g_settings;

} // namespace seneca

#endif // SENECA_SETTINGS_H
