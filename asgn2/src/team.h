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
#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {
    class Team {
        std::string m_name{};           // Name of the team
        Character** m_characters{};     // Dynamic array of character pointers
        int m_numberOfCharacters{};     // Number of character instances in the team

    public:
        Team();
        Team(const char* name);

        Team(const Team& src);
        Team& operator=(const Team& src);
        ~Team();

        Team(Team&& src);
        Team& operator=(Team&& src);

        // Finds the index of a character by name
        int findMember(const std::string& name);

        // Adds a character if not already present
        void addMember(const Character* c);

        // Removes a character by name
        void removeMember(const std::string& c);

        // Returns a pointer to a character at an index
        Character* operator[](size_t idx) const;

        // Displays the team members
        void showMembers() const;
    };
}
#endif // SENECA_TEAM_H
