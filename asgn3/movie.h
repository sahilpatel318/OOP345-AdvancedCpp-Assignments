#pragma once
/*
 Name : SAHIL HARESHBHAI PATEL
 Email: shpatel27@myseneca.ca
 Student ID: 173793225
 Date: July 18, 2025

 I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
 This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include "mediaItem.h"  // Base abstract class
#include "settings.h"   // For accessing display configuration
#include <string>
#include <ostream>

namespace seneca
{
    /*
     * The Movie class represents a media item of type Movie.
     * It inherits from the abstract base class MediaItem and implements the display logic.
     */
    class Movie : public MediaItem
    {
    public:
        /*
         * Default constructor - initializes an empty Movie with default base values.
         */
        Movie();

        /*
         * Parameterized constructor - initializes a Movie with given title, year, and summary.
         * @param title   : Title of the movie
         * @param year    : Year the movie was released
         * @param summary : Summary or description of the movie
         */
        Movie(const std::string &title, unsigned short year, const std::string &summary);

        /*
         * Overrides the pure virtual display function from MediaItem.
         * Outputs movie details to the provided output stream in table or detailed format.
         * @param out : output stream where movie details are printed
         */
        void display(std::ostream &out) const override;

        /*
         * Static factory method that creates a dynamically allocated Movie
         * from a comma-separated string in the format "TITLE,YEAR,SUMMARY".
         * @param strMovie : CSV string representing the movie data
         * @return pointer to a new Movie object
         */
        static Movie *createItem(const std::string &strMovie);
    };
}

#endif // SENECA_MOVIE_H
