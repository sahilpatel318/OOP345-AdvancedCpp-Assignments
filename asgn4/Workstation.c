/*
Name: SAHIL HARESHBHAI PATEL
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 1/08/2025

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#pragma once
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <iostream>
#include <string>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
	// Global deques used to store orders in different states
	extern std::deque<seneca::CustomerOrder> g_pending;    // Orders waiting to be processed
	extern std::deque<seneca::CustomerOrder> g_completed;  // Orders that have been fully completed
	extern std::deque<seneca::CustomerOrder> g_incomplete; // Orders that couldn't be completed

	// Workstation class represents a single step in an assembly line.
	// Inherits from Station, so it has item name, quantity, etc.
	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders;        // Orders currently at this station
		Workstation* m_pNextStation = nullptr;     // Pointer to the next station in the chain

	public:
		// Constructor - initializes a workstation from a string record
		Workstation(const std::string& str) : Station(str) {}

		// Disallow copy assignment
		Workstation& operator=(Workstation&&) = delete;

		// Adds a new customer order to the back of the queue
		Workstation& operator+=(CustomerOrder&& newOrder);

		// Disallow move construction
		Workstation(Workstation&&) = delete;

		// Fills the item for the front order in the queue (if possible)
		void fill(std::ostream& os);

		// Attempts to move the order to the next station or final queue
		bool attemptToMoveOrder();

		// Sets the pointer to the next station in the chain
		void setNextStation(Workstation* station);

		// Returns the pointer to the next station
		Workstation* getNextStation() const;

		// Displays information about this station and the next station in the chain
		void display(std::ostream& os) const;
	};

} // namespace seneca

#endif // !SENECA_WORKSTATION_H#pragma once
