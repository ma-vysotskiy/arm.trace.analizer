/*
 * StrategyResolver.hpp
 *
 *  Created on: Apr 30, 2013
 *      Author: mvis
 */

#pragma once

#include <vector>
#include "../Strategy/Strategy.hpp"
#include "../Strategy/PTM/PTMStrategy.hpp"
#include <iostream>
#include <iterator>
#include <stack>
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
			uint32_t pos = str.find(getStrategiesNames(i) + "=\"", 0);
			string::iterator it = str.begin();
			it += pos + getStrategiesNames(i).size() + 2;
			string::iterator start = it;
			stack<char> st;
			string result = "";
			while (it != str.end()) {
				string::iterator next = it + 1;
				if ((*it) == '=' && (*next) == '\"') {
					st.push('"');
					it++;
				} else if ((*it) == '\"') {
					if (st.empty()) {
						result = string(start, it);
						break;
					} else {
						st.pop();
					}
				}
				it++;
			}
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
