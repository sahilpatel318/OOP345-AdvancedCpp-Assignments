/*
Name: Sahil Hareshbhai Patel
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 20/06/2025

I declare that this submission is the result of my own work and I only copied the code 
that my professor provided to complete my assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.
*/

#include <iostream>
#include "guild.h"

namespace seneca {

    // Default constructor
    Guild::Guild() {
    }

    // Constructor that initializes the guild name
    Guild::Guild(const char* name) {
        m_name = name;
    }

    // Copy constructor
    Guild::Guild(const Guild& src) {
        *this = src;
    }

    // Copy assignment operator
    Guild& Guild::operator=(const Guild& src) {
        if (this != &src) {
            delete[] m_characters;

            m_name = src.m_name;
            m_characters = new Character * [src.m_numberOfCharacters];
            m_numberOfCharacters = src.m_numberOfCharacters;

            // Perform a shallow copy (characters are NOT cloned)
            for (int i = 0; i < m_numberOfCharacters; ++i) {
                m_characters[i] = src.m_characters[i];
            }
        }
        return *this;
    }

    // Destructor
    Guild::~Guild() {
        delete[] m_characters;
    }

    // Move constructor
    Guild::Guild(Guild&& src) {
        *this = std::move(src);
    }

    // Move assignment operator
    Guild& Guild::operator=(Guild&& src) {
        if (this != &src) {
            delete[] m_characters;

            m_name = src.m_name;
            m_characters = src.m_characters;
            m_numberOfCharacters = src.m_numberOfCharacters;

            // Reset source
            src.m_name = "";            
            src.m_characters = nullptr;
            src.m_numberOfCharacters = 0;
        }
        return *this;
    }

    // Finds a character by name and returns its index, or -1 if not found
    int Guild::findMember(const std::string& name) {
        for (int i = 0; i < m_numberOfCharacters; ++i) {
            if (m_characters[i]->getName() == name) {
                return i;
            }
        }
        return -1;
    }

    // Adds a character to the guild, if not already present
    void Guild::addMember(Character* c) {
        int idx = findMember(c->getName());
        if (idx >= 0) {
            return;
        }

        m_numberOfCharacters++;
        Character** characters = new Character * [m_numberOfCharacters];
        for (int i = 0; i < m_numberOfCharacters - 1; ++i) {
            characters[i] = m_characters[i];
        }

        // Increase the character's max health and reset it
        c->setHealthMax(c->getHealthMax() + 300);
        c->setHealth(c->getHealthMax());

        characters[m_numberOfCharacters - 1] = c;

        delete[] m_characters;
        m_characters = characters;
    }

    // Removes a character from the guild
    void Guild::removeMember(const std::string& c) {
        int idx = findMember(c);
        if (idx < 0) {
            return;
        }

        // Reduce the character's health and reset
        m_characters[idx]->setHealthMax(m_characters[idx]->getHealthMax() - 300);
        m_characters[idx]->setHealth(m_characters[idx]->getHealthMax());

        for (int i = idx; i < m_numberOfCharacters - 1; ++i) {
            m_characters[i] = m_characters[i + 1];
        }

        m_numberOfCharacters--; // Decrease count
    }

    // Returns a pointer to the character at the given index
    Character* Guild::operator[](size_t idx) const {
        if (idx >= (size_t)m_numberOfCharacters) {
            return nullptr;
        }
        return m_characters[idx];
    }

    // Displays the guild and its members
    void Guild::showMembers() const {
        if (m_name.empty() && m_numberOfCharacters == 0) {
            std::cout << "No guild." << std::endl;
        } else {
            std::cout << "[Guild] " << m_name << std::endl;

            for (int i = 0; i < m_numberOfCharacters; ++i) {
                std::cout << "    " << (i + 1) << ": " << *(m_characters[i]) << std::endl;
            }
        }
    }

} // namespace seneca
