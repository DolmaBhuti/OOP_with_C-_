/*
* Name: Dolma Bhuti
* Seneca email: dbhuti1@myseneca.ca
* Seneca ID: 015438138
*  DATE: /04/21
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_LINE_MANAGER_H
#define SDDS_LINE_MANAGER_H
#include <vector>
#include "Workstation.h"
namespace sdds {
	class LineManager {
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder = 0;
		Workstation* m_firstStation = nullptr;
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}



#endif