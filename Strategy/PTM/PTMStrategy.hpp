/*
 * PTMStrategy.hpp
 *
 *  Created on: Apr 30, 2013
 *      Author: mvis
 */

#pragma once

#include "../../Strategy/Strategy.hpp"
#include "../../Strategy/PTM/PTMSettings.hpp"

class CPTMStrategy : public CStrategy {
public:
	CPTMStrategy() :
			CStrategy(0, new CPTMSettings()) {
	}

	~CPTMStrategy() {
		delete settings;
	}

	list<CPacket> parse(list<CData> data) {
	}

	void setSettings(string str) {
	}

	void output(list<CPacket> packets) {
	}
};
