/*
 * Strategy.hpp
 *
 *  Created on: Apr 30, 2013
 *      Author: mvis
 */

#pragma once

#include <list>

using namespace std;

class CStrategy {
public:
	virtual list<CPacket> parse(list<CData> data)=0;

	virtual void output(list<CPacket> packets)=0;

	const uint32_t& getIdentifier() {
		return identifier;
	}

protected:
	const uint32_t identifier;
};
