/*
Name: SAHIL HARESHBHAI PATEL
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 1/08/2025

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "LineManager.h"
#include <sstream>

namespace seneca {

    // Constructor - reads the configuration file and links Workstations together in the correct order
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream inputFile(file);
        if (!inputFile) {
            // Throw an error if the file cannot be opened
            throw std::runtime_error("Error: Unable to open file " + file);
        }

        std::string line;
        // Read each line from the configuration file
        while (std::getline(inputFile, line)) {
            std::istringstream record(line);
            std::string currentStation, nextStation;

            // Extract current station name (before '|')
            std::getline(record, currentStation, '|');
            // Extract next station name (after '|')
            std::getline(record, nextStation);

            // Find the current station from the provided stations list
            auto currentIt = std::find_if(stations.begin(), stations.end(),
                [&currentStation](Workstation* station) {
                    return station->getItemName() == currentStation;
                });

            // Find the next station from the provided stations list
            auto nextIt = std::find_if(stations.begin(), stations.end(),
                [&nextStation](Workstation* station) {
                    return station->getItemName() == nextStation;
                });

            // If the current station exists, add it to the active line
            if (currentIt != stations.end()) {
                m_activeLine.push_back(*currentIt);

                // If the next station exists, link the current station to it
                if (nextIt != stations.end()) {
                    (*currentIt)->setNextStation(*nextIt);
                }
            }
        }

        // Determine the first station in the line (one that no other station points to)
        m_firstStation = *std::find_if(stations.begin(), stations.end(),
            [&stations](Workstation* station) {
                return std::none_of(stations.begin(), stations.end(),
                    [station](Workstation* other) {
                        return other->getNextStation() == station;
                    });
            });

        // Set total number of customer orders to process
        m_cntCustomerOrder = g_pending.size();
    }

    // Reorders the stations in the correct sequence starting from the first station
    void LineManager::reorderStations() {
        std::vector<Workstation*> reordered;
        Workstation* current = m_firstStation;

        // Follow the chain of next stations to build the ordered list
        while (current) {
            reordered.push_back(current);
            current = current->getNextStation();
        }

        // Update the active line with the reordered sequence
        m_activeLine = std::move(reordered);
    }

    // Executes a single iteration of the assembly line process
    bool LineManager::run(std::ostream& os) {
        static size_t iteration = 0;
        ++iteration;

        os << "Line Manager Iteration: " << iteration << std::endl;

        // If there are pending orders, move the first one to the first station
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        // Fill orders at each station
        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [&os](Workstation* station) {
                station->fill(os);
            });

        // Attempt to move orders from each station to the next one
        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [](Workstation* station) {
                station->attemptToMoveOrder();
            });

        // Return true if all orders are either completed or incomplete
        return (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder);
    }

    // Displays the current configuration of the line
    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [&os](Workstation* station) {
                station->display(os);
            });
    }

} // namespace seneca
