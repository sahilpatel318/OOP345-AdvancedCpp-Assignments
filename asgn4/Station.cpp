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
#include "Station.h"
#include "Utilities.h"

namespace seneca {

	// Initialize static members
	size_t Station::m_widthField = 0;      // Holds the max width for field formatting
	size_t Station::id_generator = 0;      // Used to assign unique IDs to each Station

	// Custom constructor - parses a formatted string to initialize station details
	Station::Station(const std::string& str) {
		Utilities util;          // Utility object for token extraction
		size_t next_pos = 0;     // Current position in the parsing string
		bool more = true;        // Flag to indicate if there are more tokens to extract

		// Extract name of the item
		m_name = util.extractToken(str, next_pos, more);

		// Extract serial number (convert to unsigned long)
		m_serialNumber = std::stoul(util.extractToken(str, next_pos, more));

		// Extract quantity in stock
		m_qtyInStock = std::stoul(util.extractToken(str, next_pos, more));

		// Update max field width if this item's name is longer than the current max
		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}

		// Extract item description
		m_desc = util.extractToken(str, next_pos, more);

		// Assign unique ID to this station
		m_id = ++id_generator;
	}

	// Returns the unique ID for this station
	size_t Station::getId() const {
		return m_id;
	}

	// Returns the name of the item this station handles
	const std::string& Station::getItemName() const {
		return m_name;
	}

	// Returns the current serial number, then increments it for the next call
	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}

	// Returns the current quantity of items in stock
	size_t Station::getQuantity() const {
		return m_qtyInStock;
	}

	// Reduces the stock quantity by 1 (ensuring it doesn’t go below zero)
	void Station::updateQuantity() {
		if (m_qtyInStock > 0) {
			--m_qtyInStock;
		}
	}

	// Displays station information
	void Station::display(std::ostream& os, bool full) const {
		// Always print: ID | NAME | SERIAL |
		os << std::setw(3) << std::right << std::setfill('0') << m_id << " | "
			<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | "
			<< std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

		// If 'full' is true, also print quantity and description
		if (full) {
			os << std::setw(4) << std::setfill(' ') << m_qtyInStock << " | "
				<< m_desc;
		}
		os << std::endl;
	}

} // namespace seneca
