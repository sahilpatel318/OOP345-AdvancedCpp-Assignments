/*
Name: SAHIL HARESHBHAI PATEL
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 1/08/2025

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include <iostream>
#include <string>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"

namespace seneca {

    size_t CustomerOrder::m_widthField = 0;

    // Constructor that parses a record string to initialize a customer order
    CustomerOrder::CustomerOrder(const std::string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        // Extract customer name
        m_name = util.extractToken(record, next_pos, more);
        // Extract product name
        m_product = util.extractToken(record, next_pos, more);

        // Count how many items are in the order by extracting tokens until no more
        m_cntItem = 0;
        size_t temp_pos = next_pos;
        while (more) {
            util.extractToken(record, temp_pos, more);
            m_cntItem++;
        }

        // Allocate dynamic array of Item pointers based on count
        m_lstItem = new Item * [m_cntItem];
        for (size_t i = 0; i < m_cntItem; ++i) {
            // Create new Item for each token
            m_lstItem[i] = new Item(util.extractToken(record, next_pos, more));
        }

        // Update static field width for formatting if needed
        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
    }

    // Copy constructor disabled: copying not allowed
    CustomerOrder::CustomerOrder(const CustomerOrder&) {
        throw std::runtime_error("Copying CustomerOrder is not allowed.");
    }

    // Move constructor transfers ownership of resources
    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        *this = std::move(other);
    }

    // Move assignment operator transfers ownership safely
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            // Free existing resources
            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            // Transfer data members from other
            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            // Reset other's members to safe state
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }
        return *this;
    }

    // Destructor frees allocated memory
    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    // Returns true if all items in the order are filled
    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) {
                // Found item not filled, so order not complete
                return false;
            }
        }
        // All items filled
        return true;
    }

    // Returns true if the item with the given name is filled (or doesn't exist)
    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        // Check if any matching item is unfilled
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                return false;  // Found matching item that is not filled
            }
        }
        // No matching unfilled item found, so return true
        return true;
    }

    // Attempts to fill items in this order using inventory from the given station
    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; ++i) {
            // Check if this item matches the station and is not filled yet
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    // Assign serial number from station to item and mark filled
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;

                    // Decrement station inventory quantity
                    station.updateQuantity();

                    // Log successful fill
                    os << "    Filled " << m_name << ", " << m_product
                       << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    break;  // Only fill one item per call
                }
                else {
                    // Station out of stock, unable to fill this item
                    os << "    Unable to fill " << m_name << ", " << m_product
                       << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    // Displays the entire customer order and status of each item
    void CustomerOrder::display(std::ostream& os) const {
        // Print customer name and product ordered
        os << m_name << " - " << m_product << std::endl;
        // Print each item with its serial number and fill status
        for (size_t i = 0; i < m_cntItem; ++i) {
            os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber
               << "] " << std::setw(m_widthField) << std::setfill(' ') << std::left
               << m_lstItem[i]->m_itemName << " - "
               << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }

} // namespace seneca
