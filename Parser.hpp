/*
 * Parser.hpp
 *
 *  Created on: May 27, 2013
 *      Author: mvis
 */

#pragma once

#include <map>
#include <set>
#include <utility>
#include <istream>
#include <stdint.h>
#include <iostream>
#include <algorithm>

#include "Defines.hpp"
#include "Packet/Packet.hpp"
#include "Exceptions/notenoughdata.hpp"
#include "Strategy/StrategyResolver.hpp"

using namespace std;

class CParser {
	typedef map<uint32_t, dataType> idtodataType;
	typedef map<uint32_t, packetType> idtopacketType;
public:
	static CParser& getInstance() {
		static CParser theSingleInstance;
		return theSingleInstance;
	}

	void parse(istream& is, uint32_t mask) throw (notenough_data) {
		idtodataType IDtoData;
		dataType rawData = getRawData(is, mask);
		IDtoData = extractID(rawData);
		// output
		printIdToData(IDtoData);
		// process strategies
		IDtoPackets = processData(IDtoData);
	}
protected:
	idtodataType extractID(const dataType rawData) {
		uint32_t currID = 0;
		uint32_t count = 0;
		idtodataType IDtoData;
//		cout << "raw Data" << endl;
//		for (dataType::const_iterator it = rawData.cbegin();
//				it != rawData.cend(); it++) {
//			cout << (int) it->data << endl;
//		}
		try {
			for (dataType::const_iterator it = rawData.cbegin();
					(count + 16) <= rawData.size(); advance(it, 16)) {
				// count variable placed here for crutch ;)
				count += 16;
				dataType::const_iterator lastByteIt = it;
				advance(lastByteIt, 15);
				if (lastByteIt == rawData.end()) {
					throw notenough_data();
				}
				for (uint32_t i = 0; i < 15; i++) {
					CData currByte = *(it + i);

					uint8_t lastBit = (((*lastByteIt).data
							>> ((uint32_t) (i / 2))) & 1);
					bool isID = ((currByte.data) & 0x1) && (i % 2 == 0);
					if (!(i % 2)) {
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
							idtodataType::iterator dataIt = IDtoData.find(
									currID);
							// found - add
							if (dataIt != IDtoData.end()) {
								dataIt->second.push_back(nextByte);
								cout << "Push data " << (int) nextByte.data
										<< endl;
							} else {
								// if cannot find old id that is really bad
								cout << "Error! Old ID " << nextByte.data
										<< " was not found!" << endl;
							}
							// now new id takes effect
							currID = currByte.data >> 1;
						}
						// find new id
						idtodataType::iterator dataIt = IDtoData.find(currID);
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
						idtodataType::iterator dataIt = IDtoData.find(currID);
						if (dataIt != IDtoData.end()) {
							cout << "Push data " << (int) currByte.data << endl;
							dataIt->second.push_back(currByte);
						} else {
							cout << "Warning! Current ID " << currByte.data
									<< " was not found!" << endl;
						}
					}
				}
			}
		} catch (notenough_data& e) {
			cout << "Warning! " << e.what() << endl;
		}
		return IDtoData;
	}

	void printIdToData(const idtodataType IDtoData) const {
		for (idtodataType::const_iterator it = IDtoData.cbegin();
				it != IDtoData.cend(); it++) {
			cout << dec << it->first << ":" << endl;
			for (dataType::const_iterator dataIt = it->second.cbegin();
					dataIt != it->second.cend(); dataIt++) {
				cout << "\t" << hex << (int) dataIt->data << "\t" << dec
						<< (int) dataIt->ts << endl;
			}
		}
	}

	map<uint32_t, packetType> processData(const idtodataType IDtoData) {
		map<uint32_t, packetType> idToPacketsMap;
		CStrategyResolver& csr = CStrategyResolver::getInstance();
		for_each(IDtoData.begin(), IDtoData.end(),
				[&](pair<uint32_t, dataType> p) {
					uint32_t stratId = p.first;
					try {
						const CStrategy& strat = csr.getStrategyById(stratId);
						idtodataType::const_iterator dataIt = IDtoData.find(
								stratId);
						if (dataIt != IDtoData.cend()) {
							idToPacketsMap[stratId] = strat.parse(dataIt->second);
							strat.output(idToPacketsMap[stratId]);
						}} catch(strategy_error& e) {
						cout <<"Warning! Strategy with id " << stratId << " not found!" <<endl;
					}
				});
		return idToPacketsMap;
	}

	dataType getRawData(istream& is, const uint32_t mask) {
		dataType rawData;
		uint32_t ts, value, bits;
		std::string scale;
		uint32_t bytesInWord = mask / 8;
		while (!is.eof()) {
			is >> std::dec >> ts;
			is >> scale;
			is >> std::hex >> value;
			is >> bits;
			if (!is.fail() && (bits < 100)) {
				for (uint32_t i = 0; i < bytesInWord; i++) {
					CData data;
					data.data = (value >> 8 * i) & 0xff;
					data.ts = ts;
					rawData.push_back(data);
					cout << dec << ts << "\t" << hex << (int) data.data << " | "
							<< bits << endl;
				}
			} else {
//				throw 0;
			}
		}
		removeSyncData(rawData);
		return rawData;
	}
private:

	void removeSyncData(dataType& rawData) {
		dataType::iterator it = rawData.begin();
		while (it != rawData.end()) {
			if (it->data == 0xff) {
				uint32_t ffcount = 0;
				dataType::iterator mem = it;
				it++;
				while ((it->data == 0xff) && (it != rawData.end())) {
					ffcount++;
					it++;
				}
				if ((it->data == 0x7f) && (it != rawData.end())) {
					ffcount++;
					it++;
				}
				if ((ffcount == 1) || (ffcount == 3)) {
					it = rawData.erase(mem, it);
				}
			} else {
				it++;
			}
		}

	}

	CParser() {
	}
	CParser(const CParser& root) {
	}
	CParser& operator=(const CParser&) {
	}
	idtopacketType IDtoPackets;
}
;
