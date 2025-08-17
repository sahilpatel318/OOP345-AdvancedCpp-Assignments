/*
Name: SAHIL HARESHBHAI PATEL
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 1/08/2025

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "Utilities.h"
#include "Station.h"

namespace seneca {

    // Initialize the static delimiter character (default: newline)
    char Utilities::m_delimiter = '\n';

    // Sets the field width for the current Utilities object
    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth; // store the provided width
    }

    // Returns the current field width
    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    // Extracts a token from the provided string starting at next_pos
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        // If position is already past the string length, nothing to extract
        if (next_pos >= str.length()) {
            more = false;
            return "";
        }

        // Find the position of the next delimiter
        size_t pos = str.find(m_delimiter, next_pos);
        std::string token;

        // If delimiter found, extract substring up to delimiter
        if (pos != std::string::npos) {
            token = str.substr(next_pos, pos - next_pos);
            next_pos = pos + 1; // move position past delimiter
            more = true;        // there might be more tokens
        }
        else {
            // No delimiter found: take the rest of the string
            token = str.substr(next_pos);
            next_pos = str.length(); // move to end
            more = false;            // no more tokens left
        }

        // Trim leading and trailing whitespace from the token
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        // If token is empty after trimming, throw an exception
        if (token.empty()) {
            more = false;
            throw "No token found!";
        }

        // Update field width if this token is longer than current width
        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }

        return token; // return the cleaned token
    }

    // Sets the static delimiter character for all Utilities instances
    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    // Returns the current delimiter character
    const char Utilities::getDelimiter() {
        return m_delimiter;
    }

} // namespace seneca
