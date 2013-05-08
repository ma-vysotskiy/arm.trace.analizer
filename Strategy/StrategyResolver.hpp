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

class CStrategyResolver {

public:
	CStrategyResolver() {
		strategies.push_back(new CPTMStrategy());
	}

	~CStrategyResolver() {
		for (int i = 0; i < strategies.size(); i++) {
			delete strategies[i];
		}
	}



	static const string strategiesNames[] = { "PTM" };

private:
	vector<CStrategy*> strategies;
};
