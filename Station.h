/*
* Name: Dolma Bhuti
* Seneca email: dbhuti1@myseneca.ca
* Seneca ID: 015438138
*  DATE: 23/03/21
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_STATIONS_H
#define SDDS_STATIONS_H
#include <iostream>
namespace sdds {
	class Station {
		int m_stationId = 0;
		std::string m_itemName;
		std::string m_description;
		size_t m_serialNumber = 0;
		size_t m_quantity = 0;
		static unsigned m_widthField;
		static int id_generator;
	public:
		Station(const std::string str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}


#endif