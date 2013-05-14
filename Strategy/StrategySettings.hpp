/*
 * StrategySettings.hpp
 *
 *  Created on: Apr 30, 2013
 *      Author: mvis
 */

#pragma once
#include <string>
#include <map>

using namespace std;

class CStrategySettings {
public:
	CStrategySettings() :
			id(-1) {
	}

	virtual ~CStrategySettings() {
	}

	virtual void init(string str) = 0;

	uint32_t get(string str) {
		uint32_t result = -1;
		if (settings.find(str) != settings.end()) {
			result = (settings.find(str))->second;
		}
		return result;
	}
protected:
	uint32_t id;
	map<string, uint32_t> settings;
};
