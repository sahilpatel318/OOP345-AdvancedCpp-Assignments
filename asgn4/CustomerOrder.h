/*
Name: SAHIL HARESHBHAI PATEL
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 1/08/2025

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#pragma once
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Station.h"

namespace seneca {

	// Structure to hold details of a single item in the order
	struct Item
	{
		std::string m_itemName;        // name of the item
		size_t m_serialNumber{ 0 };    // serial number of the item
		bool m_isFilled{ false };      // flag to check if the item is filled

		Item(const std::string& src) : m_itemName(src) {}; // constructor initializing item name
	};

	// Class to manage and store customer order information
	class CustomerOrder {

		// name of the customer placing the order
		std::string m_name{ "" };

		// name of the product being ordered
		std::string m_product{ "" };

		// total number of items in the order
		size_t m_cntItem{ 0 };

		// dynamic array of Item pointers (each element represents one ordered item)
		Item** m_lstItem{ nullptr };

		// stores the maximum width of any field for formatting display
		static size_t m_widthField;

	public:

		// default constructor
		CustomerOrder() = default;

		// constructor that initializes object from a string record
		CustomerOrder(const std::string& str);

		// copy constructor (defined but may have restricted use)
		CustomerOrder(const CustomerOrder& src);

		// copy assignment operator is deleted to prevent copying
		CustomerOrder& operator=(const CustomerOrder& src) = delete;

		// move constructor to transfer resources
		CustomerOrder(CustomerOrder&& src) noexcept;

		// move assignment operator to transfer resources
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;

		// destructor to release allocated memory
		~CustomerOrder();

		// checks if the entire order is filled
		bool isOrderFilled() const;

		// checks if a specific item in the order is filled
		bool isItemFilled(const std::string& itemName) const;

		// attempts to fill a single item in the order using a given Station
		void fillItem(Station& station, std::ostream& os);

		// displays the order details
		void display(std::ostream& os) const;
	};

} //namespace seneca	

#endif // !SENECA_CUSTOMERORDER_H
