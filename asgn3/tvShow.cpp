/*
 Name : SAHIL HARESHBHAI PATEL
 Email: shpatel27@myseneca.ca
 Student ID: 173793225
 Date: July 18, 2025

 I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
 This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "tvShow.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "settings.h"

namespace seneca
{
    // Default constructor - initializes MediaItem with empty values and show ID as empty
    TvShow::TvShow() : MediaItem("", "", 0), m_id("") {}

    // Parameterized constructor - initializes ID, title, year, and summary
    TvShow::TvShow(const std::string &id, const std::string &title, unsigned short year, const std::string &summary)
        : MediaItem(title, summary, year), m_id(id) {}

    // Displays TV show information in table or detailed format based on global settings
    void TvShow::display(std::ostream &out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";  // Prefix for TvShow
            out << std::left << std::setfill('.') << std::setw(50) << getTitle() << " | ";
            out << std::right << std::setfill(' ') << std::setw(2) << m_episodes.size() << " | ";
            out << std::setw(4) << getYear() << " | ";

            // Handle summary trimming
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << getSummary();
                else
                    out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << getSummary();
            out << std::endl;
        }
        else  // Detailed view with episode list
        {
            out << getTitle() << " [" << getYear() << "]\n";
            out << std::string(getTitle().size() + 7, '-') << '\n';

            // Display wrapped summary
            size_t pos = 0;
            while (pos < getSummary().size())
            {
                out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            // Display each episode
            for (const auto &episode : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    S" << std::setw(2) << episode.m_season
                    << "E" << std::setw(2) << episode.m_numberInSeason << " ";

                if (!episode.m_title.empty())
                    out << episode.m_title << '\n';
                else
                    out << "Episode " << episode.m_numberOverall << '\n';

                pos = 0;
                while (pos < episode.m_summary.size())
                {
                    out << "            " << episode.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }

            out << std::string(getTitle().size() + 7, '-') << std::setfill(' ') << '\n';
        }
    }

    // Creates a new TvShow object from a CSV-formatted string
    TvShow *TvShow::createItem(const std::string &strTvShow)
    {
        if (strTvShow.empty() || strTvShow[0] == '#')
        {
            throw "Not a valid show.";
        }

        // Expected format: "ID,TITLE,YEAR,SUMMARY"
        std::string temp = strTvShow;
        size_t pos = 0;

        // Parse ID
        pos = temp.find(',');
        std::string id = temp.substr(0, pos);
        MediaItem::trim(id);
        temp = temp.substr(pos + 1);

        // Parse TITLE
        pos = temp.find(',');
        std::string title = temp.substr(0, pos);
        MediaItem::trim(title);
        temp = temp.substr(pos + 1);

        // Parse YEAR
        pos = temp.find(',');
        std::string strYear = temp.substr(0, pos);
        MediaItem::trim(strYear);
        unsigned short year = static_cast<unsigned short>(std::stoi(strYear));
        temp = temp.substr(pos + 1);

        // Remaining is SUMMARY
        MediaItem::trim(temp);
        std::string summary = temp;

        // Create and return a new TvShow object
        return new TvShow(id, title, year, summary);
    }

    // Calculates the average episode length in seconds
    double TvShow::getEpisodeAverageLength() const
    {
        return std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0,
                               [&](double total, const TvEpisode &ep)
                               {
                                   return total + ep.m_length;
                               }) /
               m_episodes.size();
    }

    // Returns a list of episode titles that are 1 hour (3600s) or longer
    std::list<std::string> TvShow::getLongEpisodes() const
    {
        std::list<std::string> longEpisode;

        std::for_each(m_episodes.begin(), m_episodes.end(), [&](const TvEpisode &episode)
                      {
                if (episode.m_length >= 3600)
                {
                    longEpisode.push_back(episode.m_title);
                } });
        return longEpisode;
    }

    // Converts a time string in "HH:MM:SS" or "HH.MM.SS" format to total seconds
    unsigned int TvShow::calculateSeconds(std::string &strTime)
    {
        // Replace delimiters with spaces
        if (strTime.find(':') != std::string::npos)
        {
            strTime.replace(strTime.find(':'), 1, " ");
        }
        if (strTime.find(':') != std::string::npos)
        {
            strTime.replace(strTime.find(':'), 1, " ");
        }
        if (strTime.find('.') != std::string::npos)
        {
            strTime.replace(strTime.find('.'), 1, " ");
        }

        // Parse hours, minutes, seconds
        std::stringstream ss(strTime);
        unsigned int hours = 0, minutes = 0, seconds = 0;
        ss >> hours >> minutes >> seconds;
        return hours * 3600 + minutes * 60 + seconds;
    }
}
