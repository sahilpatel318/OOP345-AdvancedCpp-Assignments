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
#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"

namespace seneca {

    // The Rogue class is a character that uses a dagger for attacks,
    // combined with customizable abilities for attack and defense.
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense;           // Base defense rating
        int m_baseAttack;            // Base attack rating
        FirstAbility_t m_firstAbility;    // First special ability
        SecondAbility_t m_secondAbility;  // Second special ability
        seneca::Dagger m_weapon;           // The weapon used by the Rogue

    public:
        // Constructor
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax) {
            m_baseAttack = baseAttack;
            m_baseDefense = baseDefense;
        }

        // Copy constructor
        Rogue(const Rogue& src) : CharacterTpl<T>(src) {
            m_baseAttack = src.m_baseAttack;
            m_baseDefense = src.m_baseDefense;
            m_firstAbility = src.m_firstAbility;
            m_secondAbility = src.m_secondAbility;
            m_weapon = src.m_weapon;
        }

        // Returns total attack amount (base attack + weapon damage doubled)
        int getAttackAmnt() const override {
            return m_baseAttack + 2 * m_weapon.m_damage;
        }

        // Returns the defense rating
        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        // Returns a cloned copy of this character
        Character* clone() const override {
            return new Rogue(*this);
        }

        // Perform an attack on another character
        void attack(Character* enemy) override {
            std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;

            // Activate abilities
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);

            // Final damage after ability effects
            int dmg = getAttackAmnt();
            m_firstAbility.transformDamageDealt(dmg);
            m_secondAbility.transformDamageDealt(dmg);

            std::cout << "    Rogue deals " << dmg << " melee damage!" << std::endl;

            // Inflict damage
            enemy->takeDamage(dmg);
        }

        // Receive damage after applying defenses and abilities
        void takeDamage(int dmg) override {
            std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;

            // Apply defense
            std::cout << "    Rogue has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

            dmg -= m_baseDefense;

            if (dmg < 0) {
                dmg = 0;
            }

            // Apply abilities
            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);

            // Final damage application
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}
#endif // SENECA_ROGUE_H
