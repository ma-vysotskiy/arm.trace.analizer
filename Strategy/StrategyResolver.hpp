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
#include "../Exceptions/strategyerror.hpp"
#include "../Exceptions/notfounderror.hpp"

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
		for (uint32_t i = 0; i < strategies.size(); i++) {
			try {
				pair<string, string> res = CUtils::getInternalOptions(str,
						getStrategiesNames(i));
				strategies[i]->setSettings(res.second);
				str = res.first;
				uint32_t id = strategies[i]->getOption("Id");
				IDtoIndex[id] = i;
			} catch (notfound_error &e) {
				cout << "Warning! Options for strategy "
						<< getStrategiesNames(i) << " not found!" << endl;
			}
		}
	}

	const CStrategy& getStrategy(uint32_t index) throw (strategy_error) {
		if ((index >= strategies.size()) && (index < 0)) {
			throw strategy_error();
		}
		return *strategies[index];
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
	map<uint32_t, uint32_t> IDtoIndex;
};
