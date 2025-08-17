/*
Name: Sahil Hareshbhai Patel
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 20/06/2025

I declare that this submission is the result of my own work and I only copied the code 
that my professor provided to complete my assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.
*/

#pragma once
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {

    // The Guild class manages a group of character instances,
    // allowing adding, removing, and displaying members.
    class Guild {
        std::string m_name{};           // Name of the guild
        Character** m_characters{};     // Dynamic array of character pointers
        int m_numberOfCharacters{};     // Number of characters in the guild

    public:
        Guild();
        Guild(const char* name);

        Guild(const Guild& src);
        Guild& operator=(const Guild& src);
        ~Guild();

        Guild(Guild&& src);
        Guild& operator=(Guild&& src);

        // Finds the index of a character by name
        int findMember(const std::string& name);

        // Adds a character to the guild
        void addMember(Character* c);

        // Removes a character from the guild by name
        void removeMember(const std::string& c);

        // Returns a pointer to a character at a given index
        Character* operator[](size_t idx) const;

        // Displays the guild and its members
        void showMembers() const;
    };
}

#endif // SENECA_GUILD_H
