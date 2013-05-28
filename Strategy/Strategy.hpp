/*
 * Strategy.hpp
 *
 *  Created on: Apr 30, 2013
 *      Author: mvis
 */

#pragma once

#include <list>
#include <string>

#include "../Defines.hpp"
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

	virtual CStrategy* newInstance() =0;
	virtual packetType parse(dataType data) const=0;

	virtual void output(packetType packets) const=0;

	virtual void setSettings(string str) {
	}

	uint32_t getOption(string s) const {
		return settings->get(s);
	}

	const uint32_t& getIdentifier() {
		return identifier;
	}

protected:
	const uint32_t identifier;
	CStrategySettings* settings;
};
