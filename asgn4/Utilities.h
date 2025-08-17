/*
Name: SAHIL HARESHBHAI PATEL
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 1/08/2025

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {

	class Utilities
	{
		// Length of the token field, defaults to 1
		size_t m_widthField = 1;

		// Character used to separate tokens (shared across all instances)
		static char m_delimiter;

	public:

		// Sets the field width for the current object
		void setFieldWidth(size_t newWidth);

		// Returns the current field width
		size_t getFieldWidth() const;

		// Extracts a token from the given string starting at next_pos
		// - Updates next_pos to the position after the extracted token
		// - Sets 'more' to true if there are more tokens, false otherwise
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		// Sets the delimiter to the provided character (affects all Utilities objects)
		static void setDelimiter(char newDelimiter);

		// Returns the current delimiter character
		const static char getDelimiter();
	};

} // namespace seneca

#endif // !SENECA_UTILITIES_H#pragma once
