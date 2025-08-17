/*
Name: Sahil Hareshbhai Patel
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 20/06/2025

I declare that this submission is the result of my own work and I only copied the code 
that my professor provided to complete my assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.
*/

#include "team.h"

namespace seneca {

    // Default constructor: creates an empty team
    Team::Team() {
    }

    // Constructor with team name
    Team::Team(const char* name) {
        m_name = name;
    }

    // Copy constructor
    Team::Team(const Team& src) {
        *this = src;
    }

    // Copy assignment operator
    Team& Team::operator=(const Team& src) {
        if (this != &src) {
            // Deallocate existing character instances
            for (int i = 0; i < m_numberOfCharacters; ++i) {
                delete m_characters[i];
            }
            delete[] m_characters;

            // Copy name
            m_name = src.m_name;

            // Allocate space and deep copy characters
            m_characters = new Character * [src.m_numberOfCharacters];
            m_numberOfCharacters = src.m_numberOfCharacters;

            for (int i = 0; i < m_numberOfCharacters; ++i) {
                m_characters[i] = src.m_characters[i]->clone();
            }
        }
        return *this;
    }

    // Destructor
    Team::~Team() {
        for (int i = 0; i < m_numberOfCharacters; ++i) {
            delete m_characters[i];
        }
        delete[] m_characters;
    }

    // Move constructor
    Team::Team(Team&& src) {
        *this = std::move(src);
    }

    // Move assignment operator
    Team& Team::operator=(Team&& src) {
        if (this != &src) {
            // Deallocate existing character instances
            for (int i = 0; i < m_numberOfCharacters; ++i) {
                delete m_characters[i];
            }
            delete[] m_characters;

            // Transfer resources
            m_name = src.m_name;
            m_characters = src.m_characters;
            m_numberOfCharacters = src.m_numberOfCharacters;

            // Reset the source
            src.m_name = "";            
            src.m_characters = nullptr;
            src.m_numberOfCharacters = 0;
        }
        return *this;
    }

    // Finds a character by name and returns its index, or -1 if not found
    int Team::findMember(const std::string& name) {
        for (int i = 0; i < m_numberOfCharacters; ++i) {
            if (m_characters[i]->getName() == name) {
                return i;
            }
        }
        return -1;
    }

    // Adds a character to the team if it doesn’t already exist
    void Team::addMember(const Character* c) {
        int idx = findMember(c->getName());
        if (idx >= 0) {
            return; // The character already exists
        }

        m_numberOfCharacters++;
        Character** characters = new Character * [m_numberOfCharacters];
        for (int i = 0; i < m_numberOfCharacters - 1; ++i) {
            characters[i] = m_characters[i];
        }
        characters[m_numberOfCharacters - 1] = c->clone();

        delete[] m_characters;
        m_characters = characters;
    }

    // Removes a character from the team
    void Team::removeMember(const std::string& c) {
        int idx = findMember(c);
        if (idx < 0) {
            return; // Not found
        }

        delete m_characters[idx];
        for (int i = idx; i < m_numberOfCharacters - 1; ++i) {
            m_characters[i] = m_characters[i + 1];
        }
        m_numberOfCharacters--; // Decrease character count
    }

    // Returns the character pointer at the given index, or nullptr if out of range
    Character* Team::operator[](size_t idx) const {
        if (idx >= (size_t)m_numberOfCharacters) {
            return nullptr;
        }
        return m_characters[idx];
    }

    // Displays team information
    void Team::showMembers() const {
        if (m_name.empty() && m_numberOfCharacters == 0) {
            std::cout << "No team." << std::endl;
        } else {
            std::cout << "[Team] " << m_name << std::endl;

            for (int i = 0; i < m_numberOfCharacters; ++i) {
                std::cout << "    " << (i + 1) << ": " << *(m_characters[i]) << std::endl;
            }
        }
    }

} // namespace seneca
