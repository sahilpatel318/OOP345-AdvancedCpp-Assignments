/*
 Name : SAHIL HARESHBHAI PATEL
 Email: shpatel27@myseneca.ca
 Student ID: 173793225
 Date: July 18, 2025

 I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
 This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "spellChecker.h"

using namespace std;

namespace seneca
{
	// Constructor: Loads bad/good word pairs from a given file
	SpellChecker::SpellChecker(const char *filename)
	{
		// Initialize replacement counters to 0
		for (size_t i = 0; i < 6; i++)
		{
			m_misCount[i] = 0;
		}

		std::ifstream file(filename);
		if (!file)
		{
			// Throw runtime error if file can't be opened
			throw std::runtime_error("Could not open file: " + std::string(filename));
		}

		size_t i = 0;
		std::string line;
		// Read each line from the file up to 6 word pairs
		while (std::getline(file, line))
		{
			if (i >= 6 || line.empty())
			{
				break;
			}

			// Expected format: "BAD_WORD GOOD_WORD"
			std::stringstream ss(line);
			ss >> m_badWords[i] >> m_goodWords[i];
			i++;
		}
	}

	// Overloaded function call operator: Applies word replacements in the provided text
	void SpellChecker::operator()(std::string &text)
	{
		for (size_t i = 0; i < 6; i++)
		{
			std::string::size_type pos = 0;
			// Replace all occurrences of m_badWords[i] with m_goodWords[i]
			while ((pos = text.find(m_badWords[i], pos)) != std::string::npos)
			{
				text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
				pos += m_goodWords[i].length();  // Move past the replaced word
				m_misCount[i]++;  // Track how many times each bad word is replaced
			}
		}
	}

	// Displays how many times each word was replaced
	void SpellChecker::showStatistics(std::ostream &out) const
	{
		out << "Spellchecker Statistics\n";
		for (size_t i = 0; i < 6; i++)
		{
			out << std::left << std::setw(15) << m_badWords[i] << ": " << m_misCount[i]
				 << " replacements\n";
		}
	}
}
