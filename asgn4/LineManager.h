/*
Name: SAHIL HARESHBHAI PATEL
Email: shpatel27@myseneca.ca
Student ID: 173793225
Date: 1/08/2025

I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#pragma once
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Workstation.h"

namespace seneca {

	class LineManager {
		// All workstations currently active in the assembly line (in order of processing)
		std::vector<Workstation*> m_activeLine;

		// Total number of customer orders that need to be processed
		size_t m_cntCustomerOrder{ 0 };

		// Pointer to the first workstation in the assembly line
		Workstation* m_firstStation{ nullptr };

	public:
		// Constructor - sets up the assembly line using a configuration file and available stations
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);

		// Reorders the stations in the correct processing sequence
		void reorderStations();

		// Runs one iteration of the assembly line process
		// Returns true if all orders have been filled, false otherwise
		bool run(std::ostream& os);

		// Displays the current configuration of the assembly line
		void display(std::ostream& os) const;
	};

} // namespace seneca

#endif // !SENECA_LINEMANAGER_H#pragma once
