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
		for (int i = 0; i < strategies.size(); i++) {
			try {
				pair<string, string> res = CUtils::getInternalOptions(str,
						getStrategiesNames(i));
				strategies[i]->setSettings(res.second);
				str = res.first;
			} catch (notfound_error &e) {
				//
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
};
