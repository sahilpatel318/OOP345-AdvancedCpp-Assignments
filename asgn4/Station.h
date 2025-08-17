/*
Name: SAHIL HARESHBHAI PATEL
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 1/08/2025

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#pragma once
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>

namespace seneca {

	class Station {

		// Unique station ID number
		size_t m_id{};

		// Name of the item handled by this station
		std::string m_name{ "" };

		// Description of the item
		std::string m_desc{ "" };

		// Serial number assigned to the next item produced
		size_t m_serialNumber{};

		// Quantity of items currently in stock
		size_t m_qtyInStock{};

		// Maximum width of any field when printing item details (shared by all stations)
		static size_t m_widthField;

		// Used to generate unique station IDs
		static size_t id_generator;

	public:

		// Default constructor
		Station() = default;

		// Custom constructor - initializes a station using a formatted string
		Station(const std::string& str);

		// Returns the station's unique ID
		size_t getId() const;

		// Returns the name of the item for this station
		const std::string& getItemName() const;

		// Returns the next serial number for the current item, then increments it
		size_t getNextSerialNumber();

		// Returns the current quantity in stock
		size_t getQuantity() const;

		// Decreases the quantity in stock by 1 (never going below 0)
		void updateQuantity();

		// Displays station information
		// If 'full' is true, shows full details; otherwise shows brief details
		void display(std::ostream& os, bool full) const;
	};

} // namespace seneca

#endif // !SENECA_STATION_H#pragma once
