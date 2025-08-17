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
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "character.h"
#include "characterTpl.h"

namespace seneca {

    // Barbarian character class template with customizable ability and weapons.
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseDefense{};           // Base defense value
        int m_baseAttack{};            // Base attack value
        Ability_t m_ability{};         // Special ability
        Weapon_t m_weapon[2]{};        // Primary and secondary weapons

    public:
        // Constructor initializing character and weapons
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon,
                  Weapon_t secondaryWeapon) : CharacterTpl<T>(name, healthMax) {
            m_baseAttack = baseAttack;
            m_baseDefense = baseDefense;
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }

        // Copy constructor
        Barbarian(const Barbarian& src) : CharacterTpl<T>(src) {
            m_baseAttack = src.m_baseAttack;
            m_baseDefense = src.m_baseDefense;
            m_weapon[0] = src.m_weapon[0];
            m_weapon[1] = src.m_weapon[1];
            m_ability = src.m_ability;
        }

        // Calculate total attack amount: base attack plus half damage of each weapon
        int getAttackAmnt() const override {
            return m_baseAttack + (static_cast<double>(m_weapon[0]) / 2) + (static_cast<double>(m_weapon[1]) / 2);
        }

        // Return base defense amount
        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        // Clone this character
        Character* clone() const override {
            return new Barbarian(*this);
        }

        // Attack an enemy character
        void attack(Character* enemy) override {
            std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
            m_ability.useAbility(this);

            int dmg = getAttackAmnt();
            m_ability.transformDamageDealt(dmg);

            std::cout << "    Barbarian deals " << dmg << " melee damage!" << std::endl;
            enemy->takeDamage(dmg);
        }

        // Take damage after applying defense and ability effects
        void takeDamage(int dmg) override {
            std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

            dmg -= m_baseDefense;
            dmg = dmg < 0 ? 0 : dmg;

            m_ability.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}

#endif // SENECA_BARBARIAN_H
