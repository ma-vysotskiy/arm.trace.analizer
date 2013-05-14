/*
 * Strategy.hpp
 *
 *  Created on: Apr 30, 2013
 *      Author: mvis
 */

#pragma once

#include <list>

#include "../Strategy/StrategySettings.hpp"
#include "../Packet/Packet.hpp"

using namespace std;

class CStrategy {
public:
	CStrategy(uint32_t ident, CStrategySettings* setting) :
			identifier(ident), settings(setting) {
	}
	virtual ~CStrategy() {
	}

	virtual list<CPacket> parse(list<CData> data)=0;

	virtual void output(list<CPacket> packets)=0;

	virtual void setSettings(string str) {
	}

	const uint32_t& getIdentifier() {
		return identifier;
	}

protected:
	const uint32_t identifier;
	CStrategySettings* settings;
};
