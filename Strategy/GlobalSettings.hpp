/*
 * GlobalSettings.hpp
 *
 *  Created on: May 15, 2013
 *      Author: mvis
 */

#pragma once

#include "../Defines.hpp"
#include "../Exceptions/enumerror.hpp"
#include "../Strategy/StrategySettings.hpp"
#include "../Common/Utils.hpp"

using namespace std;

#undef enumBody
#define enumBody \
e_begin(field) \
	e_member(output, output) \
e_end

class CGlobalSettings : public CStrategySettings {
public:
	static CGlobalSettings& getInstance() {
		static CGlobalSettings theSingleInstance;
		return theSingleInstance;
	}

	void init(string str) {

	}
	//add enum declaration
#include "../Enum/enum_helper_pub.h"
private:
	//strings asociated with enum
#include "../Enum/enum_helper_pri.h"

	CGlobalSettings() {
	}
	CGlobalSettings(const CGlobalSettings& root) {
	}
	CGlobalSettings& operator=(const CGlobalSettings&) {
	}

};
