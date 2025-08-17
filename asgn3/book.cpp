/*
 Name : SAHIL HARESHBHAI PATEL
 Email: shpatel27@myseneca.ca
 Student ID: 173793225
 Date: July 18, 2025

 I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
 This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "book.h"
#include "settings.h"
#include <sstream>
#include <iomanip>

namespace seneca
{
    // Default constructor initializing base MediaItem and member variables
    Book::Book() : MediaItem("", "", 0), m_author(""), m_country(""), m_price(0) {}

    // Display function outputs book information in either table or detailed format
    void Book::display(std::ostream &out) const
    {
        if (g_settings.m_tableView)  // If table view is enabled
        {
            out << "B | ";  // Prefix for book type
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";  // Title with fixed width
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";  // Country code
            out << std::setw(4) << this->getYear() << " | ";  // Year of publication
            out << std::left;

            // Output summary with character limit if set
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();  // Full summary
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";  // Truncated with ellipsis
            }
            else
            {
                out << this->getSummary();  // No limit on summary length
            }
            out << std::endl;
        }
        else  // Detailed view (non-table)
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";  // Basic book details
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';  // Title underline

            // Output summary in wrapped format according to max width
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            // Closing underline
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    // Static factory method to create a Book object from a CSV string
    Book *Book::createItem(const std::string &strBook)
    {
        if (strBook.empty() || strBook[0] == '#')
        {
            throw "Not a valid book.";  // Ignore comments or empty lines
        }

        // Expected format: "AUTHOR,TITLE,COUNTRY,PRICE,YEAR,SUMMARY"
        std::string temp = strBook;
        size_t pos = 0;

        // Extract AUTHOR
        pos = temp.find(',');
        std::string strAuthor = temp.substr(0, pos);
        MediaItem::trim(strAuthor);
        temp = temp.substr(pos + 1);

        // Extract TITLE
        pos = temp.find(',');
        std::string strTitle = temp.substr(0, pos);
        MediaItem::trim(strTitle);
        temp = temp.substr(pos + 1);

        // Extract COUNTRY
        pos = temp.find(',');
        std::string strCountry = temp.substr(0, pos);
        MediaItem::trim(strCountry);
        temp = temp.substr(pos + 1);

        // Extract PRICE
        pos = temp.find(',');
        std::string strPrice = temp.substr(0, pos);
        double price = std::stod(strPrice);  // Convert string to double
        temp = temp.substr(pos + 1);

        // Extract YEAR
        pos = temp.find(',');
        std::string strYear = temp.substr(0, pos);
        unsigned short year = static_cast<unsigned short>(std::stoi(strYear));  // Convert to unsigned short
        temp = temp.substr(pos + 1);

        // Remaining string is SUMMARY
        MediaItem::trim(temp);
        std::string summary = temp;

        // Return a new Book instance created with parsed values
        return new Book(strTitle, summary, year, strAuthor, strCountry, price);
    }
}
