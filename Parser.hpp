/*
 * Parser.hpp
 *
 *  Created on: May 27, 2013
 *      Author: mvis
 */

#pragma once

#include <map>
#include <utility>
#include <istream>
#include <stdint.h>
#include <iostream>

#include "Defines.hpp"
#include "Packet/Packet.hpp"
#include "Exceptions/notenoughdata.hpp"
#include "Strategy/StrategyResolver.hpp"

using namespace std;

class CParser {
public:
	static CParser& getInstance() {
		static CParser theSingleInstance;
		return theSingleInstance;
	}
	void parse(istream& is, uint32_t mask) throw (notenough_data) {
		map<uint32_t, dataType> IDtoData;
		dataType rawData = getRawData(is);
		uint32_t currID = 0;
		for (dataType::iterator it = rawData.begin(); it != rawData.end(); it +=
				16) {
			dataType::iterator lastByteIt = it + 15;
			if (lastByteIt == rawData.end()) {
				throw notenough_data();
			}
			CData lastByte = *lastByteIt;
			for (uint32_t i = 0; i < 15; i++) {
				CData currByte = *(it + i);
				uint8_t lastBit = ((lastByte.data >> i) & 1);
				bool isID = (currByte.data) & 0x1;
				if (!i % 2) {
					currByte.data = (currByte.data & (~1)) | lastBit;
				}
				if (isID) {
					// ID
					CData nextByte;
					if (!lastBit) {
						// lastBit == 0 new id takes effect immediately
						currID = currByte.data >> 1;
					} else {
						// lastBit == 1 add next byte to old id
						i++;
						// next byte
						nextByte = *(it + i);
						// find old id
						map<uint32_t, dataType>::iterator dataIt =
								IDtoData.find(currID);
						// found - add
						if (dataIt != IDtoData.end()) {
							dataIt->second.push_back(nextByte);
						} else {
							// if cannot find old id that is really bad
							cout << "Error! Old ID " << nextByte.data
									<< " was not found!" << endl;
						}
						// now new id takes effect
						currID = currByte.data >> 1;
					}
					// find new id
					map<uint32_t, dataType>::iterator dataIt = IDtoData.find(
							currID);
					// found - changing to new id
					if (dataIt != IDtoData.end()) {
						cout << "Info! Changing ID to " << currID << "!"
								<< endl;
					} else {
						// not found - add new id
						cout << "Info! New ID is " << currID << "!" << endl;
						IDtoData.insert(make_pair(currID, dataType()));
					}
				} else {
					// DATA
					map<uint32_t, dataType>::iterator dataIt = IDtoData.find(
							currID);
					if (dataIt != IDtoData.end()) {
						dataIt->second.push_back(currByte);
					} else {
						cout << "Warning! Current ID " << currByte.data
								<< " was not found!" << endl;
					}
				}
			}
		}
		// process strategies
		for (map<uint32_t, dataType>::iterator it = IDtoData.begin();
				it != IDtoData.end(); it++) {
			cout << dec << it->first << ":" << endl;
			for (dataType::iterator dataIt = it->second.begin();
					dataIt != it->second.end(); dataIt++) {
				cout << "\t" << hex << (int) dataIt->data << endl;
			}
		}
		try {
			CStrategyResolver& csr = CStrategyResolver::getInstance();
			for (uint32_t i = 0;; i++) {
				const CStrategy& strat = csr.getStrategy(i);
				uint32_t stratId = strat.getOption("Id");
				map<uint32_t, dataType>::iterator dataIt = IDtoData.find(
						stratId);
				if (dataIt != IDtoData.end()) {
					packetType parseRes = strat.parse(dataIt->second);
					strat.output(parseRes);
				}
			}
		} catch (strategy_error& e) {
		}
	}
private:

	dataType getRawData(istream& is) {
		dataType rawData;
		uint32_t ts, value, bits;
		std::string scale;
		while (!is.eof()) {
			CData data;
			CData data2;
			is >> std::dec >> ts;
			is >> scale;
			is >> std::hex >> value;
			is >> bits;
			if (!is.fail()) {
				data.data = value & 0xff;
				data.ts = ts;
				data2.data = (value >> 8) & 0xff;
				data2.ts = ts;
				rawData.push_back(data);
				rawData.push_back(data2);
			}
//			cout << dec << ts << "\t" << hex << (int) data2.data << " "
//					<< (int) data.data << " | " << bits << endl;
		}
		return rawData;
	}

	CParser() {
	}
	CParser(const CParser& root) {
	}
	CParser& operator=(const CParser&) {
	}
	map<uint32_t, packetType> IDtoPackets;
}
;
