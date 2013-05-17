/*
 * PTMSettings.hpp
 *
 *  Created on: May 8, 2013
 *      Author: mvis
 */

#pragma once

#include <string>

#include "../../Defines.hpp"
#include "../../Strategy/StrategySettings.hpp"
#include "../../Strategy/Settings.hpp"
#include "../../Common/Utils.hpp"
#include "../../Exceptions/notfounderror.hpp"

using namespace std;

class CPTMSettings : public CStrategySettings {
public:
	void init(string str) {
		settings = CUtils::parseOptions(str);
	}
};
