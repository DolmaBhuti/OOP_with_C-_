/*
* Name: Dolma Bhuti
* Seneca email: dbhuti1@myseneca.ca
* Seneca ID: 015438138
*  DATE: 29/03/21
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_CUSTOMER_ORDER_H
#define SDDS_CUSTOMER_ORDER_H
#include <iostream>
#include "Utilities.h"
#include "Station.h"
namespace sdds {
	class CustomerOrder {
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

		std::string m_name;  //customer name
		std::string m_product; //name of product being assembled
		size_t m_cntItem = 0; //count of number of items in the customers order
		Item** m_lstItem = nullptr;  //dynamic array of pointer.points to object of type Item
		static size_t m_widthField;// – the maximum width of a field, used for display purposes
	
	public:
		CustomerOrder() {}
		~CustomerOrder();
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& src);
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
	
}


#endif