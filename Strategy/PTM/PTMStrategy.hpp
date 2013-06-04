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
#include <stdint.h>
#include <memory>
#include <utility>

using namespace std;

#include "../../Defines.hpp"
#include "../../Packet/Data.hpp"
#include "../../Strategy/Strategy.hpp"
#include "../../Strategy/PTM/PTMSettings.hpp"
#include "../../Packet/PTM/PTMPackets.hpp"
#include "../../Packet/Packet.hpp"

class CPTMStrategy : public CStrategy {
public:
	CPTMStrategy() :
			CStrategy(0, new CPTMSettings()) {
	}

	virtual CStrategy* newInstance() {
		return new CPTMStrategy();
	}

	~CPTMStrategy() {
		delete settings;
	}

	packetType parse(dataType data) const {
		packetType packets;
		for (dataType::iterator it = data.begin(); it < data.end(); it++) {
			switch (it->data) {
			case Async:
				{
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
					while (dataEnd->data == Async) {
						dataEnd++;
						counter++;
					}
					if (dataEnd->data != 0x80) {
						cout << settings->get("Id")
								<< " Warning: Async packets must end with byte \'0x80\'!"
								<< endl;
					} else {
						dataEnd++;
						counter++;
					}
					// we must have at least 1 header byte and 4 data bytes
					if (counter < 5) {
						//warning!
						cout << settings->get("Id")
								<< " Warning: Async packets size less than 5 bytes!"
								<< endl;
					}
					// copy data
					packetData.insert(packetData.begin(), dataStrart, dataEnd);
					// form packet object
					packets.insert(packets.end(),
							make_shared < CPTMAsyncPacket
									> (header->data, packetData));

					// increment iterator so we wont process same data twice
					// counter -1 because we will get it++ in a for loop
					advance(it, counter - 1);
				}
				break;
			case Isync:
				{
					dataType packetData;
					dataType::iterator header = it;
					dataType::iterator dataStrart;
					dataType::iterator dataEnd;
					// now it points to first data byte
					it++;
					dataStrart = it;
					dataEnd = it;
					uint32_t counter = 5;
					uint32_t cc = settings->get(
							CUtils::enumToString<CPTMSimpleOption>(
									CPTMSimpleOption::CycleCount));
					advance(dataEnd, counter);
					packetData.insert(packetData.end(), dataStrart, dataEnd);
					dataStrart = dataEnd;
					if (cc) {

						if (dataEnd->data & 0x40) {
							dataEnd++;
							counter++;
							while (dataEnd->data & 0x80) {
								dataEnd++;
								counter++;
							}
						}
						dataEnd++;
						counter++;
						packetData.insert(packetData.end(), dataStrart,
								dataEnd);
						dataStrart = dataEnd;
					} else {
						for (uint32_t i = 0; i < 5; i++) {
							packetData.insert(packetData.end(),
									CData(0x0, dataEnd->ts));
						}
					}

					uint32_t ci = settings->get(
							CUtils::enumToString<CPTMSimpleOption>(
									CPTMSimpleOption::ContextID));
					if (ci) {
						counter += 4;
						advance(dataEnd, 4);
						packetData.insert(packetData.end(), dataStrart,
								dataEnd);
					} else {
						for (uint32_t i = 0; i < 4; i++) {
							packetData.insert(packetData.end(),
									CData(0x0, dataEnd->ts));
						}
					}

					packets.insert(packets.end(),
							make_shared < CPTMIsyncPacket
									> (header->data, packetData));

					advance(it, counter - 1);
				}
				break;
			case WaypointUp:
				{
					dataType packetData;
					dataType::iterator header = it;
					dataType::iterator dataStrart;
					dataType::iterator dataEnd;
					// now it points to first data byte
					it++;
					dataStrart = it;
					dataEnd = it;
					uint32_t counter = 1;
					// extract address
					{
						//if we have address then 7ths bit is 1
						while (dataEnd->data & 0x80) {
							dataEnd++;
							counter++;
						}
						//check if we have waypoint information byte
						if (dataEnd->data & 0x60) {
							dataEnd++;
							counter++;
						}
					}
					dataEnd++;
					counter++;
					packetData.insert(packetData.begin(), dataStrart, dataEnd);

					::std::shared_ptr<CPTMWaypointPacket> p = make_shared
							< CPTMWaypointPacket > (header->data, packetData);
					p->instrSetCurrState = CPTMWaypointPacket::ARM;
					packets.insert(packets.end(), p);

					advance(it, counter - 2);
				}
				break;
			case Trigger:
				{
					dataType packetData;
					dataType::iterator header = it;
					::std::shared_ptr<CPTMTriggerPacket> p = make_shared
							< CPTMTriggerPacket > (header->data, packetData);
					packets.insert(packets.end(), p);
				}
				break;
			case ContextID:
				{
					dataType packetData;
					dataType::iterator header = it;
					dataType::iterator dataStrart;
					dataType::iterator dataEnd;
					uint32_t counter = 0;
					uint32_t cis = settings->get(
							CUtils::enumToString<CPTMComplexOption>(
									CPTMComplexOption::ContextIdSize));
					if (cis) {
						// now it points to first data byte
						it++;

						dataStrart = it;
						dataEnd = it;
						for (uint32_t i = 0; i < cis; i++) {
							dataEnd++;
							counter++;
						}

						for (uint32_t i = 0; i < (4 - cis); i++) {
							// insert zero bytes to make packet think that context ID always 32 bits long
							packetData.insert(packetData.begin(),
									CData(0x0, it->ts));

						}
						packetData.insert(packetData.begin(), dataStrart,
								dataEnd);
					}
					::std::shared_ptr<CPTMContextIDPacket> p = make_shared
							< CPTMContextIDPacket > (header->data, packetData);
					packets.insert(packets.end(), p);
					advance(it, counter - 1);
				}
				break;
			case Timestamp:
			case Timestamp | 0x4:
				{
					dataType packetData;
					dataType::iterator header = it;
					dataType::iterator dataStrart;
					dataType::iterator dataEnd;
					// now it points to first data byte
					it++;
					dataStrart = it;
					dataEnd = it;
					uint32_t counter = 1;
					// check how many timestamp bytes we have
					{

						while (dataEnd->data & 0x80) {
							dataEnd++;
							counter++;
						}
						dataEnd++;
						counter++;

						// add zero bytes if needed
						uint32_t tmpCounter = 8 - counter;
						while (tmpCounter) {
							packetData.insert(packetData.begin(),
									CData(0x0, it->ts));
							tmpCounter--;
						}

						// copy data
						packetData.insert(packetData.begin(), dataStrart,
								dataEnd);
						// to avoid coping twice
						dataStrart = dataEnd;

					}
					// now cycle count
					{
						uint32_t cc = settings->get(
								CUtils::enumToString<CPTMSimpleOption>(
										CPTMSimpleOption::CycleCount));
						if (cc) {
							if (dataEnd->data & 0x40) {
								dataEnd++;
								counter++;
								while (dataEnd->data & 0x80) {
									dataEnd++;
									counter++;
								}
								dataEnd++;
								counter++;
							}
						} else {
							for (uint32_t i = 0; i < 5; i++) {
								packetData.insert(packetData.end(),
										CData(0x0, dataEnd->ts));
							}
						}
					}
					packetData.insert(packetData.end(), dataStrart, dataEnd);

					::std::shared_ptr<CPTMTimestampPacket> p = make_shared
							< CPTMTimestampPacket > (header->data, packetData);
					packets.insert(packets.end(), p);
					advance(it, counter - 2);
				}
				break;
			case ExceptionRet:
				{
					dataType packetData;
					dataType::iterator header = it;
					::std::shared_ptr<CPTMExceptionReturnPacket> p = make_shared
							< CPTMExceptionReturnPacket
							> (header->data, packetData);
					packets.insert(packets.end(), p);
				}
				break;
			case Ignore:
				{
					dataType packetData;
					dataType::iterator header = it;
					::std::shared_ptr<CPTMIgnorePacket> p = make_shared
							< CPTMIgnorePacket > (header->data, packetData);
					packets.insert(packets.end(), p);
				}
				break;
			default:
				switch (it->data & 1) {
				case Atom:
					{
						dataType packetData;
						dataType::iterator header = it;
						dataType::iterator dataStrart;
						dataType::iterator dataEnd;
						// first data byte is also a header
						dataStrart = it;
						dataEnd = it;
						uint32_t counter = 1;
						uint32_t cc = settings->get(
								CUtils::enumToString<CPTMSimpleOption>(
										CPTMSimpleOption::CycleCount));
						if (cc) {
							if (dataEnd->data & 0x40) {
								dataEnd++;
								counter++;
							}
							while (dataEnd->data & 0x80) {
								dataEnd++;
								counter++;
							}
							dataEnd++;
							packetData.insert(packetData.end(), dataStrart,
									dataEnd);
						} else {
							for (uint32_t i = 0; i < 5; i++) {
								packetData.insert(packetData.end(),
										CData(0x0, dataEnd->ts));
							}
						}

						::std::shared_ptr<CPTMAtomPacket> p = make_shared
								< CPTMAtomPacket > (header->data, packetData);
						packets.insert(packets.end(), p);
						advance(it, counter - 1);
					}
					break;
				case Branch:
					{
						dataType packetData;
						dataType::iterator header = it;
						dataType::iterator dataStrart;
						dataType::iterator dataEnd;
						// first data byte is also a header
						dataStrart = it;
						dataEnd = it + 1;
						uint32_t counter = 1;
						if (header->data & 0x80) {

							while (dataEnd->data & 0x80) {
								dataEnd++;
								counter++;
							}
							if (dataEnd->data & 0x40) {
								dataEnd++;
								counter++;
							}
							if (dataEnd->data & 0x80) {
								dataEnd++;
								counter++;
							}
							dataEnd++;
							uint32_t cc = settings->get(
									CUtils::enumToString<CPTMSimpleOption>(
											CPTMSimpleOption::CycleCount));
							if (cc) {
								if (dataEnd->data & 0x40) {
									dataEnd++;
									counter++;
								}
								while (dataEnd->data & 0x80) {
									dataEnd++;
									counter++;
								}
							}

						}

						packetData.insert(packetData.end(), dataStrart,
								dataEnd);
						uint32_t size = packetData.size();
						for (uint32_t i = 0; i < (12 - size); i++) {
							packetData.insert(packetData.end(),
									CData(0x0, dataEnd->ts));
						}

						::std::shared_ptr<CPTMBranchPacket> p = make_shared
								< CPTMBranchPacket > (header->data, packetData);
						packets.insert(packets.end(), p);
						advance(it, counter);
					}
					break;
				default:
					//print warning
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

	void output(packetType packets) const {
		const char tab = '\t';
		cout << hex << "Id: " << settings->get("Id") << endl;
		for (packetType::iterator it = packets.begin(); it != packets.end();
				it++) {
			cout << typeid(**it).name() << ": " << hex << (*it)->getHeader()
					<< endl << tab;
			dataType& data = (*it)->getData();
			for (dataType::iterator dataIt = data.begin(); dataIt != data.end();
					dataIt++) {
				cout << (uint32_t) (*dataIt).data << ", ";
			}
			cout << endl;
			for (uint32_t i = 0; i < (*it)->getLastField(); i++) {
				cout << tab << (*it)->getFieldStr(i).first << ": ";

				if ((((*it)->getHeader() == Timestamp)
						|| ((*it)->getHeader() == (Timestamp | 0x4)))
						&& (i == CPTMTimestampPacket::Timestamp)) {
					cout << (*it)->get64Field(i);
				} else {
					cout << (*it)->getField(i);
				}
				cout << endl;
			}
		}
	}
};
