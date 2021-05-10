/*
* Name: Dolma Bhuti
* Seneca email: dbhuti1@myseneca.ca
* Seneca ID: 015438138
*  DATE: 29/03/21
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "CustomerOrder.h"
#include <iomanip>
#include <vector>
namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::~CustomerOrder() {
		
			for (auto i = 0u; i < m_cntItem; ++i) {
				//std::cout << m_lstItem[i]->m_itemName << std::endl;
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
	}
	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities utils;
		bool more = true;
		size_t next_pos = 0;
		std::string lcl;
		
		if (more) {
			 lcl = utils.extractToken(str, next_pos, more);
			 m_name = lcl;
			 
		}
		if (more) {
			lcl = utils.extractToken(str, next_pos, more);
			m_product = lcl;
			
		}
		std::vector<std::string> itemArr;
		while (more) {
			
			itemArr.resize(m_cntItem);
			lcl = utils.extractToken(str, next_pos, more);
			itemArr.push_back(lcl);
		
			m_cntItem += 1;
		}
		m_lstItem = new Item*[m_cntItem];
		for (auto i = 0u; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(itemArr[i]);
		}
		if (CustomerOrder::m_widthField < utils.getFieldWidth()) {
			CustomerOrder::m_widthField = utils.getFieldWidth();
		}
		
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw "Error";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		*this = std::move(src);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			
			for (auto i = 0u; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
			m_lstItem = src.m_lstItem;
			m_cntItem = src.m_cntItem;
			m_name = src.m_name;
			m_product = src.m_product;
			
			
			src.m_lstItem = nullptr;
			src.m_cntItem = 0;
			src.m_name = "";
			src.m_product = "";
		}
		return *this;
	}
	bool CustomerOrder::isFilled() const {
		bool ok = true;
		for (auto i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled != true) {
				ok = false;
			}
		}
		return ok;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool ok = true;
		for (auto i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				ok = m_lstItem[i]->m_isFilled;
			}
		}
		return ok;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (auto i = 0u; i < m_cntItem ; i++) {
			if (station.getItemName() == m_lstItem[i]->m_itemName) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name
						<< ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]"
						<< std::endl;
				}
				else if (station.getQuantity() == 0 && m_lstItem[i]->m_isFilled == false) {
					os << "    Unable to fill " << m_name
						<< ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]"
						<< std::endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (auto i = 0u; i < m_cntItem; i++) {
			
			os << "[";
			os << std::setfill('0');
			os << std::setw(6) << std::right << m_lstItem[i]->m_serialNumber;
			os << "] ";
			os << std::setfill(' ');
			os << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName;
			os << " - ";
			if (m_lstItem[i]->m_isFilled == true) {
				os << "FILLED" << std::endl;
			}
			else {
				os << "TO BE FILLED" << std::endl;
			}
		}
	
	}
}
