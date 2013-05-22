/*
 * PTMStrategy.hpp
 *
 *  Created on: Apr 30, 2013
 *      Author: mvis
 */

#pragma once

#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

#include "../../Defines.hpp"
#include "../../Strategy/Strategy.hpp"
#include "../../Strategy/PTM/PTMSettings.hpp"
#include "../../Packet/PTM/PTMPackets.hpp"
#include "../../Packet/Packet.hpp"

class CPTMStrategy : public CStrategy {
public:
	CPTMStrategy() :
			CStrategy(0, new CPTMSettings()) {
	}

	~CPTMStrategy() {
		delete settings;
	}

	packetType parse(dataType data) {
		packetType packets;
		for (dataType::iterator it = data.begin(); it < data.end(); it++) {
			switch (it->data) {
			case Async:
				dataType packetData;
				dataType::iterator header = it;
				dataType::iterator dataStrart;
				dataType::iterator dataEnd;
				// now it points to first data byte
				it++;
				dataStrart = it;
				dataEnd = it;
				uint32_t counter = 0;
				// iterate while data bytes are 0
				while (it->data == Async) {
					dataEnd++;
					counter++;
				}
				// we must have at least 1 header byte and 4 data bytes
				if (counter < 4) {
					//warning!
					cout << "Warning: Async packets size less than 5 bytes!"
							<< endl;
				}
				// copy data
				copy(dataStrart, dataEnd, packetData.begin());
				// form packet object
				packets.push_back(CPTMAsyncPacket(*header, packetData));

				// increment iterator so we wont process same data twice
				// counter -1 because we will get it++ in a for loop
				advance(it, counter - 1);
				break;
			case Isync:
				break;
			case WaypointUp:
				break;
			case Trigger:
				break;
			case ContextID:
				break;
			case Timestamp:
			case Timestamp | 0x4:
				break;
			case ExceptionRet:
				break;
			case Ignore:
				break;
			default:
				switch (it->data & 1) {
				case Atom:
					break;
				case Branch:
					break;
				}
				break;
			}
		}

		if (packets.empty() && !data.empty()) {
			cout << "Warning: no packets formed!" << endl;
		}
		return packets;
	}
	enum Headers {
		Async = 0x0,		//b00000000
		Isync = 0x08,		//b00001000
		Atom = 0,			//b1xxxxxx0
		Branch = 1,			//bCxxxxxx1
		WaypointUp = 0x72,	//b01110010
		Trigger = 0x0c,		//b00001100
		ContextID = 0x6e,	//b01101110
		Timestamp = 0x42,	//b01000x10
		ExceptionRet = 0x76,	//b01110110
		Ignore = 0x66		//b01100110
	};

	void setSettings(string str) {
		settings->init(str);
	}

	void output(list<CPacket> packets) {
	}
};
