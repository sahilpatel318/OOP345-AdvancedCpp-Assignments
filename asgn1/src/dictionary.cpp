// Name: Sahil Hareshbhai Patel
// Seneca Student ID: 173793225
// Seneca email: shpatel27@myseneca.ca
// Date of completion: 06/06/2025
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work has 
// not been shared with any other student or 3rd party content provider.

#include "dictionary.h"
#include "settings.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

namespace seneca {

    // Default constructor - just sets everything to empty/null
    Dictionary::Dictionary() : m_words(nullptr), m_count(0) {}

    // Constructor that loads dictionary data from a file
    Dictionary::Dictionary(const char* filename) : m_words(nullptr), m_count(0) {
        if (!filename) return;  // If filename is null, nothing to load

        std::ifstream file(filename);
        if (!file.is_open()) return;  // If file can't be opened, exit

        // First pass: count how many non-empty lines there are
        std::string line;
        size_t line_count = 0;
        while (std::getline(file, line)) {
            if (!line.empty()) line_count++;
        }

        if (line_count == 0) return;  // If there's nothing in the file, we're done

        // Allocate space to hold all the words
        m_words = new Word[line_count];

        // Reset file pointer to the beginning
        file.clear();
        file.seekg(0);

        // Second pass: actually read and parse each line
        while (std::getline(file, line) && m_count < line_count) {
            if (line.empty()) continue;

            std::vector<std::string> fields;
            std::string field;
            bool in_quotes = false;

            // Parse the line manually to handle quoted CSV fields
            for (size_t i = 0; i < line.length(); ++i) {
                char c = line[i];

                if (c == '"') {
                    in_quotes = !in_quotes; // Toggle quote state
                    field += c; // Keep the quote for now
                }
                else if (c == ',' && !in_quotes) {
                    fields.push_back(field); // Found a full field
                    field.clear();
                }
                else {
                    field += c;
                }
            }
            fields.push_back(field); // Don't forget the last field

            // If we got enough fields, save the word
            if (fields.size() >= 3) {
                m_words[m_count].m_word = fields[0];
                m_words[m_count].m_pos = getPartOfSpeech(fields[1]);
                m_words[m_count].m_definition = fields[2];
                m_count++;
            }
        }
    }

    // Destructor - cleans up dynamically allocated memory
    Dictionary::~Dictionary() {
        cleanup();
    }

    // Copy constructor - creates a deep copy of another Dictionary
    Dictionary::Dictionary(const Dictionary& other) : m_words(nullptr), m_count(0) {
        copy(other);
    }

    // Copy assignment operator
    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            cleanup();    // Get rid of current data
            copy(other);  // Copy new data
        }
        return *this;
    }

    // Move constructor - takes over resources from another Dictionary
    Dictionary::Dictionary(Dictionary&& other) noexcept
        : m_words(other.m_words), m_count(other.m_count) {
        other.m_words = nullptr;
        other.m_count = 0;
    }

    // Move assignment operator
    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            cleanup(); // Clean up current
            m_words = other.m_words;
            m_count = other.m_count;
            other.m_words = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

    // Searches for a word in the dictionary and prints its definition(s)
    void Dictionary::searchWord(const char* word) {
        if (!word || !m_words) {
            std::cout << "Word '" << (word ? word : "") << "' was not found in the dictionary." << std::endl;
            return;
        }

        std::string search_word = word;
        bool found = false;
        bool first_definition = true;

        for (size_t i = 0; i < m_count; ++i) {
            if (m_words[i].m_word == search_word) {
                found = true;

                // For the first match, print the word. For the rest, just align.
                if (first_definition) {
                    std::cout << search_word;
                    first_definition = false;
                }
                else {
                    std::cout << std::string(search_word.length(), ' ');
                }

                std::cout << " - ";

                // If verbose mode is on and part of speech is known, show it
                if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                    std::cout << "(";
                    switch (m_words[i].m_pos) {
                    case PartOfSpeech::Noun: std::cout << "noun"; break;
                    case PartOfSpeech::Pronoun: std::cout << "pronoun"; break;
                    case PartOfSpeech::Adjective: std::cout << "adjective"; break;
                    case PartOfSpeech::Adverb: std::cout << "adverb"; break;
                    case PartOfSpeech::Verb: std::cout << "verb"; break;
                    case PartOfSpeech::Preposition: std::cout << "preposition"; break;
                    case PartOfSpeech::Conjunction: std::cout << "conjunction"; break;
                    case PartOfSpeech::Interjection: std::cout << "interjection"; break;
                    default: break;
                    }
                    std::cout << ") ";
                }

                // Show the actual definition
                std::cout << m_words[i].m_definition << std::endl;

                if (!g_settings.m_show_all) {
                    return; // If only one definition is needed, exit
                }
            }
        }

        // If we looped through and didn’t find anything
        if (!found) {
            std::cout << "Word '" << search_word << "' was not found in the dictionary." << std::endl;
        }
    }

    // Helper method to convert part-of-speech string to enum
    PartOfSpeech Dictionary::getPartOfSpeech(const std::string& pos_str) const {
        if (pos_str == "n." || pos_str == "n. pl.") return PartOfSpeech::Noun;
        if (pos_str == "adv.") return PartOfSpeech::Adverb;
        if (pos_str == "a.") return PartOfSpeech::Adjective;
        if (pos_str == "v." || pos_str == "v. i." || pos_str == "v. t." || pos_str == "v. t. & i.")
            return PartOfSpeech::Verb;
        if (pos_str == "prep.") return PartOfSpeech::Preposition;
        if (pos_str == "pron.") return PartOfSpeech::Pronoun;
        if (pos_str == "conj.") return PartOfSpeech::Conjunction;
        if (pos_str == "interj.") return PartOfSpeech::Interjection;
        return PartOfSpeech::Unknown;
    }

    // Frees up any dynamically allocated memory
    void Dictionary::cleanup() {
        delete[] m_words;
        m_words = nullptr;
        m_count = 0;
    }

    // Copies data from another Dictionary (deep copy)
    void Dictionary::copy(const Dictionary& other) {
        m_count = other.m_count;
        if (m_count > 0) {
            m_words = new Word[m_count];
            for (size_t i = 0; i < m_count; ++i) {
                m_words[i] = other.m_words[i];
            }
        }
    }
}
