/*
* Name: Dolma Bhuti
* Seneca email: dbhuti1@myseneca.ca
* Seneca ID: 015438138
*  DATE: 23/03/21
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	unsigned Station::m_widthField = 0;
	int Station::id_generator = 0;


	Station::Station(const std::string str) {
		size_t next_pos = 0;
		bool more;
		Utilities lcl;
		m_itemName = lcl.extractToken(str, next_pos, more);
		
		if (Station::m_widthField < lcl.getFieldWidth()) {
			Station::m_widthField = lcl.getFieldWidth();
		}
		
		m_serialNumber = stoi( lcl.extractToken(str, next_pos, more));
		m_quantity = stoi(lcl.extractToken(str, next_pos, more));
		if (Station::m_widthField < lcl.getFieldWidth()) {
			Station::m_widthField = lcl.getFieldWidth();
		}
		
		
		
		m_description = lcl.extractToken(str, next_pos, more);
		
		++Station::id_generator;
		m_stationId = Station::id_generator;
	}
	const std::string& Station::getItemName() const {
		return m_itemName;
	}
	size_t Station::getNextSerialNumber() {
		size_t sm = m_serialNumber;
		++m_serialNumber;
		return sm;
	}
	size_t Station::getQuantity() const {
		return m_quantity;
	}
	void Station::updateQuantity() {
		if (m_quantity != 0) {
			--m_quantity;
		}
	}
	void Station::display(std::ostream& os, bool full) const {
		if (full == false) {
			os << "[";
			os << std::setfill('0');
			os << std::setw(3) << std::right << m_stationId  << "]";
			os << std::setfill(' ');
			os << " Item: " << std::setw(Station::m_widthField) << std::left << m_itemName << " [";
			os << std::setfill('0');
			os << std::setw(6) << std::right << m_serialNumber << "]" << std::endl;
			os << std::setfill(' ');
		}
		else {
			os << "[";
			os << std::setfill('0');
			os << std::setw(3) << std::right << m_stationId << "]";
			os << std::setfill(' ');
			os << " Item: " << std::setw(Station::m_widthField) << std::left << m_itemName << " [";
			os << std::setfill('0');
			os << std::setw(6) << std::right << m_serialNumber << "] ";
			os << std::setfill(' ');
			os << "Quantity: "
				<< std::setw(Station::m_widthField) << std::left << m_quantity;
			os << " Description: " << m_description << std::endl;
		}
	}
}
