/*
* Name: Dolma Bhuti
* Seneca email: dbhuti1@myseneca.ca
* Seneca ID: 015438138
*  DATE: /04/21
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include <iostream>
#include <fstream>
#include <algorithm>   
#include <string>
#include "LineManager.h"
#include "Utilities.h"


namespace sdds {

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {

		try {
			Utilities temp;
			size_t next_pos, count = 0;
			bool more = true;
			std::string record, field1 = "", field2 = "";

			temp.setDelimiter('|');

			std::ifstream filename(file);
			while (!filename.eof()) {
				next_pos = 0;
				std::getline(filename, record);

				field1 = temp.extractToken(record, next_pos, more);
				auto find = std::find_if(stations.begin(), stations.end(),
					[=](auto& lcl) -> bool {
						return lcl->getItemName() == field1;
					});

				if (find == std::end(stations)) {
					std::string err = "ERROR :" + field1 + " not found";
					throw err;
				}
				else {

					activeLine.push_back(*find);  // It loads the contents of the file,
					count += 1; 
				}

				
				if (more) {
					field2 = temp.extractToken(record, next_pos, more);
					auto find2 = std::find_if(stations.begin(), stations.end(),
						[=](auto& lcl) -> bool {  return lcl->getItemName() == field2;  });

					//if not found throw exception
					if (find2 == std::end(stations)) {

						throw std::string("ERROR :" + field2 + " not found");
					}
					else if (find2 != std::end(stations) && (field2 == activeLine.back()->getItemName())) {
						throw std::string("ERROR :" + field2 + " same as current station.");
					}
					else{
						activeLine.back()->setNextStation(*find2);

					}
				}
				else {
					field2 = "";
				}
			
			}
		auto last = std::find_if(activeLine.begin(), activeLine.end(),
			[&](const Workstation* lcl) {
				return lcl->getItemName() == "WiFi";
			});
		std::for_each(activeLine.begin(), activeLine.end(),
			[&](Workstation* lcl) {
				if (lcl == *last) {
					lcl->setNextStation();
				}
			});
		std::for_each(activeLine.begin(), activeLine.end(),
			[this]( Workstation* lcl) {
				auto first = std::find_if_not(activeLine.begin(), activeLine.end(),  //for each test station, search entire activeLine
					[&](Workstation* lcl2) {
						return lcl2->getNextStation() != activeLine.front();
					});
				
					m_firstStation = *first;
				
			});
		m_cntCustomerOrder = pending.size();

		}
		catch (std::string& msg) {  //	If something goes wrong, this constructor reports an error.
			std::cerr << msg;
		}
	}
	void LineManager::linkStations() {

		Workstation* temp = m_firstStation;
		for (auto i = 0u; i < activeLine.size(); i++) {
			if (temp != nullptr) {
				activeLine[i] = temp;
				temp = activeLine[i]->getNextStation();
			}
			
		}

		
	}  
	
	bool LineManager::run(std::ostream& os) {

		bool check = false;
		static int current_it = 1;
		static int cnt = 0;
		os << "Line Manager Iteration: " << current_it++ << std::endl;
		
		if (!pending.empty()) {
			*activeLine[0] += std::move(pending.front());
			pending.pop_front();
		}
			std::for_each(activeLine.begin(), activeLine.end(),
				[&](Workstation* lcl) {
					lcl->fill(os);  //fills_m_orders
				});
			std::for_each(activeLine.begin(), activeLine.end(),
				[&](Workstation* lcl) {
					lcl->attemptToMoveOrder();

				});
			if (m_firstStation->getNextStation() != nullptr) {
				m_firstStation = m_firstStation->getNextStation();

			}

		if ((incomplete.size() + completed.size()) == m_cntCustomerOrder) {
			check = true;
		}
		
		return check;
	}



	void LineManager::display(std::ostream& os) const {
		
		for (size_t i = 0; i < activeLine.size(); i++)
		{
			activeLine[i]->display(os);
		}

	
	}
	
}