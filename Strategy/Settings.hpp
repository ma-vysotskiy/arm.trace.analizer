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

class CGlobalSettings : public CStrategySettings {
public:
	static CGlobalSettings& getInstance() {
		static CGlobalSettings theSingleInstance;
		return theSingleInstance;
	}

	void init(string str) {

	}
private:
	CGlobalSettings() {
	}
	CGlobalSettings(const CGlobalSettings& root) {
	}
	CGlobalSettings& operator=(const CGlobalSettings&) {
	}

};

#undef enumBody
#define enumBody \
e_begin(field) \
	e_member(CycleCount, %cc) \
	e_member(ContextID, %ci) \
e_end

#define STATICFIELDGETTER

class CSimpleSettings {
public:
	CSimpleSettings(uint32_t x, dataType y) {
	}
#include "../Enum/enum_helper_pub.h"
//strings asociated with enum
#include "../Enum/enum_helper_pri.h"
};

#undef enumBody
#define enumBody \
e_begin(field) \
	e_member(Output, output) \
e_end

class CComplexSettins {
public:
	CComplexSettins(uint32_t x, dataType y) {
	}
#include "../Enum/enum_helper_pub.h"
	//strings asociated with enum
#include "../Enum/enum_helper_pri.h"
};

#undef STATICFIELDGETTER
