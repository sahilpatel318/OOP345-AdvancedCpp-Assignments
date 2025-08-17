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
#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"

namespace seneca {
    // Archer class template using a weapon type, inheriting from CharacterTpl with SuperHealth
    template <typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth> {
        int m_baseDefense{};  // Base defense value
        int m_baseAttack{};   // Base attack value
        Weapon_t m_weapon;    // Weapon equipped by the Archer

    public:
        // Constructor initializing name, health, attack, defense, and weapon
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax) {
            m_baseAttack = baseAttack;
            m_baseDefense = baseDefense;
            m_weapon = weapon;
        }

        // Copy constructor
        Archer(const Archer<Weapon_t>& src) : CharacterTpl<seneca::SuperHealth>(src) {
            m_baseAttack = src.m_baseAttack;
            m_baseDefense = src.m_baseDefense;
            m_weapon = src.m_weapon;
        }

        // Returns the total attack amount with a 30% boost
        int getAttackAmnt() const override {
            return static_cast<int>(1.3 * m_baseAttack);
        }

        // Returns the total defense amount with a 20% boost
        int getDefenseAmnt() const override {
            return static_cast<int>(1.2 * m_baseDefense);
        }

        // Clones this Archer object
        Character* clone() const override {
            return new Archer(*this);
        }

        // Attack an enemy character and display attack info
        void attack(Character* enemy) override {
            std::cout << getName() << " is attacking " << enemy->getName() << "." << std::endl;
            int dmg = getAttackAmnt();
            std::cout << "    Archer deals " << dmg << " ranged damage!" << std::endl;
            enemy->takeDamage(dmg);
        }

        // Receive damage, applying defense reduction and forwarding to base class
        void takeDamage(int dmg) override {
            std::cout << getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Archer has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;
            dmg -= m_baseDefense;
            dmg = dmg < 0 ? 0 : dmg;
            CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
        }
    };
}

#endif // SENECA_ARCHER_H
