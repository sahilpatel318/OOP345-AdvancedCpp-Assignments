#pragma once
/*
  Name : SAHIL HARESHBHAI PATEL
  Email: shpatel27@myseneca.ca
  Student ID: 173793225
  Date: July 18, 2025

  I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
  This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

namespace seneca
{
    /*
     * The SpellChecker class reads a list of misspelled (bad) words and their correct (good) versions
     * from a file, and provides functionality to correct those words in a given string of text.
     */
    class SpellChecker
    {
        std::string m_badWords[6];   // Array to store up to 6 misspelled words
        std::string m_goodWords[6];  // Array to store the corresponding correct words
        size_t m_misCount[6];        // Array to track how many replacements are made per word

    public:
        /*
         * Constructor: Loads bad/good word pairs from the provided file.
         * @param filename : path to the file containing spelling rules (format: BAD GOOD)
         * @throws std::runtime_error if the file cannot be opened
         */
        SpellChecker(const char *filename);

        /*
         * Function call operator: Applies the spell checker to a given string.
         * Replaces all occurrences of bad words with their corrected versions and
         * increments the replacement count.
         * @param text : string to be spell-checked and modified
         */
        void operator()(std::string &text);

        /*
         * Displays the number of replacements performed for each bad word.
         * @param out : output stream to display statistics (default is std::cout)
         */
        void showStatistics(std::ostream &out) const;
    };
}

#endif // SENECA_SPELLCHECKER_H
