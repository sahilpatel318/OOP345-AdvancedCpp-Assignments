#pragma once
/*
  Name : SAHIL HARESHBHAI PATEL
  Email: shpatel27@myseneca.ca
  Student ID: 173793225
  Date: July 18, 2025

  I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
  This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <sstream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include "mediaItem.h"
#include "collection.h"

namespace seneca
{
    class TvShow; // Forward declaration

    /*
     * Struct representing a single episode in a TV show.
     * Contains metadata about the episode such as title, season, runtime, etc.
     */
    struct TvEpisode
    {
        const TvShow *m_show{};                // Pointer to parent TvShow
        unsigned short m_numberOverall{};      // Global episode number
        unsigned short m_season{};             // Season number
        unsigned short m_numberInSeason{};     // Episode number within the season
        std::string m_airDate{};               // Air date string (e.g., YYYY-MM-DD)
        unsigned int m_length{};               // Duration in seconds
        std::string m_title{};                 // Episode title
        std::string m_summary{};               // Episode description
    };

    /*
     * TvShow class derived from MediaItem, represents a full TV show with multiple episodes.
     */
    class TvShow : public MediaItem
    {
        std::string m_id{};                    // Unique ID for the show (used in episode matching)
        std::vector<TvEpisode> m_episodes;     // List of episodes belonging to this show

        // Private constructors to enforce use of createItem factory function
        TvShow();
        TvShow(const std::string &id, const std::string &title, unsigned short year, const std::string &summary);

    public:
        virtual ~TvShow() noexcept = default;

        /*
         * Displays the show and its episodes in either table or detailed format.
         * @param out : output stream to write the data to
         */
        void display(std::ostream &out) const override;

        /*
         * Factory method to create a TvShow from a CSV line.
         * Format: "ID,TITLE,YEAR,SUMMARY"
         * @param strTvShow : string containing the serialized show data
         * @return pointer to a dynamically allocated TvShow object
         */
        static TvShow *createItem(const std::string &strTvShow);

        /*
         * Calculates and returns the average length of all episodes in seconds.
         */
        double getEpisodeAverageLength() const;

        /*
         * Returns a list of titles of episodes that are 1 hour or longer.
         */
        std::list<std::string> getLongEpisodes() const;

        /*
         * Converts a time string (HH:MM:SS or HH.MM.SS) into total seconds.
         * @param strTime : the time string
         * @return total number of seconds
         */
        static unsigned int calculateSeconds(std::string &strTime);

        /*
         * Adds a TvEpisode to the correct TvShow within a Collection.
         * Format of input string:
         * "ID,EPISODE_NUMBER,SEASON_NUMBER,EPISODE_IN_SEASON,AIR_DATE,LENGTH,TITLE,SUMMARY"
         * @tparam Collection_t : Collection-like type that supports operator[] and size()
         * @param col : reference to the collection of TvShow objects
         * @param strEpisode : CSV string representing one episode
         */
        template <typename Collection_t>
        static void addEpisode(Collection_t &col, const std::string &strEpisode);
    };

    // Template function must be defined in the header
    template <typename Collection_t>
    void TvShow::addEpisode(Collection_t &col, const std::string &strEpisode)
    {
        std::string temp = strEpisode;
        MediaItem::trim(temp);
        if (temp.empty() || temp[0] == '#')
        {
            throw "Not a valid episode.";
        }

        // Expected format: ID,EPISODE_NUMBER,SEASON_NUMBER,EPISODE_IN_SEASON,AIR_DATE,LENGTH,TITLE,SUMMARY
        TvEpisode episode;
        size_t pos = 0;

        // Extract Show ID and find corresponding TvShow
        pos = temp.find(',');
        std::string strId = temp.substr(0, pos);
        MediaItem::trim(strId);
        TvShow *show = nullptr;

        for (size_t i = 0; i < col.size(); i++)
        {
            show = dynamic_cast<TvShow *>(col[i]);
            if (show && show->m_id == strId)
            {
                episode.m_show = show;
                break;
            }
        }

        if (!show)
        {
            throw std::runtime_error("Invalid show ID: " + strId);
        }

        temp = temp.substr(pos + 1);

        // Extract remaining fields step-by-step
        // EPISODE_NUMBER
        pos = temp.find(',');
        std::string strEpisodeNumber = temp.substr(0, pos);
        MediaItem::trim(strEpisodeNumber);
        episode.m_numberOverall = std::stoi(strEpisodeNumber);
        temp = temp.substr(pos + 1);

        // SEASON_NUMBER
        pos = temp.find(',');
        std::string strSeason = temp.substr(0, pos);
        MediaItem::trim(strSeason);
        episode.m_season = strSeason.empty() ? 1 : std::stoi(strSeason);
        temp = temp.substr(pos + 1);

        // EPISODE_IN_SEASON
        pos = temp.find(',');
        std::string strEpisodeInSeason = temp.substr(0, pos);
        MediaItem::trim(strEpisodeInSeason);
        episode.m_numberInSeason = std::stoi(strEpisodeInSeason);
        temp = temp.substr(pos + 1);

        // AIR_DATE
        pos = temp.find(',');
        std::string strAirDate = temp.substr(0, pos);
        MediaItem::trim(strAirDate);
        episode.m_airDate = strAirDate;
        temp = temp.substr(pos + 1);

        // LENGTH (convert to seconds)
        pos = temp.find(',');
        std::string strLength = temp.substr(0, pos);
        MediaItem::trim(strLength);
        episode.m_length = calculateSeconds(strLength);
        temp = temp.substr(pos + 1);

        // TITLE
        pos = temp.find(',');
        std::string strTitle = temp.substr(0, pos);
        MediaItem::trim(strTitle);
        episode.m_title = strTitle;
        temp = temp.substr(pos + 1);

        // SUMMARY
        MediaItem::trim(temp);
        episode.m_summary = temp;

        // Add episode to the show
        show->m_episodes.push_back(episode);
    }
}

#endif // SENECA_TVSHOW_H
