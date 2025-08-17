#pragma once
/*
 Name : SAHIL HARESHBHAI PATEL
 Email: shpatel27@myseneca.ca
 Student ID: 173793225
 Date: July 18, 2025

 I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
 This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "mediaItem.h"   // Base class for Book
#include <iostream>
#include <iomanip>
#include <string>

namespace seneca
{
    // Book class derived from MediaItem, represents a book media item
    class Book : public MediaItem
    {
        // Private data members
        std::string m_author;   // Author's name
        std::string m_country;  // Country of publication
        double m_price;         // Price of the book

        // Default constructor - initializes an empty Book (used internally)
        Book();

        /* 
         * Parameterized constructor - initializes a Book object with all required data.
         * @param title    : Book title
         * @param summary  : Book summary/description
         * @param year     : Year of publication
         * @param author   : Author's name
         * @param country  : Country where the book was published
         * @param price    : Price of the book
         */
        Book(const std::string &title, const std::string &summary, unsigned short year,
             const std::string &author, const std::string &country, double price)
            : MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {}

    public:
        /*
         * Override of the base class's display function.
         * Outputs book details either in table format or full description, depending on global settings.
         * @param out : Reference to output stream where book info will be printed
         */
        void display(std::ostream &out) const override;

        /*
         * Static factory method that creates a Book object from a comma-separated string.
         * Validates and parses the input string and returns a dynamically allocated Book object.
         * @param strBook : Comma-separated string representing book data
         * @return pointer to a new Book object
         */
        static Book *createItem(const std::string &strBook);
    };
}

#endif
