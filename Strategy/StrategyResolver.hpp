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
		for (map<uint32_t, CStrategy*>::iterator it = IDtoStrategy.begin();
				it != IDtoStrategy.end(); it++) {
			delete (*it).second;
		}
	}
	static CStrategyResolver& getInstance() {
		static CStrategyResolver theSingleInstance;
		return theSingleInstance;
	}

	void init(string str) {
		for (uint32_t i = 0; i < strategies.size(); i++) {
			try {
				bool found = false;
				try {
					// wierd finding all internal options
					while (true) {
						pair<string, string> res = CUtils::getInternalOptions(
								str, getStrategiesNames(i));
						found = true;
						CStrategy* newSt = strategies[i]->newInstance();
						newSt->setSettings(res.second);
						str = res.first;
						uint32_t id = newSt->getOption("Id");
						IDtoStrategy[id] = newSt;
					}
				} catch (notfound_error &e) {
					if (!found) {
						throw;
					}
				}
			} catch (notfound_error &e) {
				cout << "Warning! Options for strategy "
						<< getStrategiesNames(i) << " not found!" << endl;
			}
		}
	}

	const CStrategy& getStrategyById(uint32_t id) throw (strategy_error) {
		map<uint32_t, CStrategy*>::iterator it = IDtoStrategy.find(id);
		if(it == IDtoStrategy.end()){
			throw strategy_error();
		}
		return *(*it).second;
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
	map<uint32_t, CStrategy*> IDtoStrategy;
};
