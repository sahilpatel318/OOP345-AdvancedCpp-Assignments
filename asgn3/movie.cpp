/*
 Name : SAHIL HARESHBHAI PATEL
 Email: shpatel27@myseneca.ca
 Student ID: 173793225
 Date: July 18, 2025

 I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
 This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "movie.h"
#include "settings.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace seneca
{
    // Default constructor initializes base MediaItem with empty strings and year 0
    Movie::Movie() : MediaItem("", "", 0) {}

    // Parameterized constructor initializes title, year, and summary
    Movie::Movie(const std::string &title, unsigned short year, const std::string &summary)
        : MediaItem(title, summary, year)
    {
    }

    // Outputs movie details depending on global settings (tableView or detailed)
    void Movie::display(std::ostream &out) const
    {
        if (g_settings.m_tableView)  // Table view enabled
        {
            out << "M | ";  // Prefix to indicate Movie
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";  // Title with padding
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";     // Year with padding
            out << std::left;

            // Print summary based on configured width limit
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();  // Full summary
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";  // Truncated summary
            }
            else
            {
                out << this->getSummary();  // No limit on summary length
            }
            out << std::endl;
        }
        else  // Detailed view
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";  // Title and year
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';  // Underline

            // Display summary line by line, according to max width setting
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << std::setfill(' ') << '\n';
        }
    }

    // Factory method to parse a CSV string and create a new Movie object
    Movie *Movie::createItem(const std::string &strMovie)
    {
        // Ignore empty or comment lines
        if (strMovie.empty() || strMovie[0] == '#')
        {
            throw "Not a valid movie.";
        }

        // Expected format: "TITLE,YEAR,SUMMARY"
        std::string temp = strMovie;
        size_t pos = 0;

        // Extract TITLE
        pos = temp.find(',');
        std::string strTitle = temp.substr(0, pos);
        MediaItem::trim(strTitle);     // Trim whitespace
        temp = temp.substr(pos + 1);

        // Extract YEAR
        pos = temp.find(',');
        std::string strYear = temp.substr(0, pos);
        MediaItem::trim(strYear);      // Trim whitespace
        unsigned short year = static_cast<unsigned short>(std::stoi(strYear));  // Convert year to unsigned short
        temp = temp.substr(pos + 1);

        // Remaining string is SUMMARY
        MediaItem::trim(temp);
        std::string summary = temp;

        // Return a dynamically allocated Movie object
        return new Movie(strTitle, year, summary);
    }
}
