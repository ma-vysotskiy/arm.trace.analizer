/*
 * StrategyResolver.hpp
 *
 *  Created on: Apr 30, 2013
 *      Author: mvis
 */

#pragma once

#include <vector>
#include <iostream>
#include <iterator>
#include <stack>

#include "../Strategy/Strategy.hpp"
#include "../Strategy/PTM/PTMStrategy.hpp"
#include "../Common/Utils.hpp"

using namespace std;

class CStrategyResolver {

public:
	~CStrategyResolver() {
		for (uint32_t i = 0; i < strategies.size(); i++) {
			delete strategies[i];
		}
	}
	static CStrategyResolver& getInstance() {
		static CStrategyResolver theSingleInstance;
		return theSingleInstance;
	}

	void init(string str) {
		for (int i = 0; i < strategies.size(); i++) {
			string result = CUtils::getInternalOptions(str, getStrategiesNames(i));
			strategies[i]->setSettings(result);
		}
	}

	const string& getStrategiesNames(uint32_t index) const {
		static const string strategiesNames[] = { "PTM" };
		return strategiesNames[index];
	}

private:
	CStrategyResolver() {
		strategies.push_back(new CPTMStrategy());
	}
	CStrategyResolver(const CStrategyResolver& root) {
	}
	CStrategyResolver& operator=(const CStrategyResolver&) {
	}

	vector<CStrategy*> strategies;
};
