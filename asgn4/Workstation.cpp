/*
Name: SAHIL HARESHBHAI PATEL
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 1/08/2025

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include <iostream>
#include <deque>
#include <string>
#include "Workstation.h"
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {

    // Global queues for tracking order states across all workstations
    std::deque<CustomerOrder> g_pending;     // Orders waiting to be processed
    std::deque<CustomerOrder> g_completed;   // Fully completed orders
    std::deque<CustomerOrder> g_incomplete;  // Orders that couldn't be completed

    // Attempts to fill the item for the first order in the queue (if any)
    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {  // Check if there’s at least one order
            m_orders.front().fillItem(*this, os); // Fill the item for this workstation
        }
    }

    // Tries to move the first order in the queue to the next station or to final queues
    bool Workstation::attemptToMoveOrder() {
        if (!m_orders.empty()) { // Only proceed if there’s an order
            // Check if the current station’s item is filled or if the station is out of stock
            if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
                
                if (m_pNextStation) { 
                    // If there's a next station, move the order there
                    *m_pNextStation += std::move(m_orders.front());
                }
                else {
                    // No next station: order is either complete or incomplete
                    if (m_orders.front().isOrderFilled()) {
                        g_completed.push_back(std::move(m_orders.front())); // Fully done
                    }
                    else {
                        g_incomplete.push_back(std::move(m_orders.front())); // Missing items
                    }
                }

                // Remove the order from this station's queue
                m_orders.pop_front();
                return true; // Successfully moved
            }
        }
        return false; // No order moved
    }

    // Links this workstation to the next one in the assembly line
    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    // Returns a pointer to the next workstation
    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    // Displays this station’s name and the name of the next station (or end of line)
    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> "
            << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line")
            << '\n';
    }

    // Adds a new order to the queue for this workstation
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder)); // Move order to avoid copying
        return *this;
    }

} // namespace seneca
