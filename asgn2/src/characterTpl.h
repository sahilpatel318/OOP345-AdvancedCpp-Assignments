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
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include <iostream>
#include "character.h"
#include "weapons.h"
#include "health.h"
#include "abilities.h"

namespace seneca {

    // A templated character class that supports different data types for health.
    template <typename T>
    class CharacterTpl : public Character {
        T m_health{};           // Current health
        int m_healthMax{};      // Maximum health

    public:
        // Constructor
        CharacterTpl(const char* name, int maxHealth) : Character(name) {
            m_healthMax = maxHealth;
            m_health = maxHealth;
        }

        // Copy constructor
        CharacterTpl(const CharacterTpl& src) : Character(src.getName().c_str()) {
            m_health = src.m_health;
            m_healthMax = src.m_healthMax;
        }

        // Reducing the character's health by a given damage value
        void takeDamage(int dmg) override {
            m_health -= dmg;

            if (m_health <= 0) {
                m_health = 0;
                std::cout << "    " << getName() << " has been defeated!" << std::endl;
            } else {
                std::cout << "    " << getName() << " took " << dmg << " damage, " 
                          << m_health << " health remaining." << std::endl;
            }
        }

        // Returns the character's current health
        int getHealth() const override {
            return static_cast<int>(m_health);
        }

        // Returns the character's maximum health
        int getHealthMax() const override {
            return m_healthMax;
        }

        // Set the character's current health
        void setHealth(int health) override {
            m_health = health;
        }

        // Set the character's maximum and current health
        void setHealthMax(int health) override {
            m_healthMax = health;
            m_health = health;
        }
    };
}
#endif // SENECA_CHARACTERTPL_H
