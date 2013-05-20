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

#define STATICFIELDGETTER
#undef enumBody
#define enumBody \
e_begin(field) \
e_end

class CBaseOption {
public:
#include "../Enum/enum_helper_pub.h"
//strings asociated with enum
#include "../Enum/enum_helper_pri.h"
};

class CBaseComplexOption : public CBaseOption {
public:
	virtual map<string, uint32_t> parseComplex(string opt, string toParse) =0;
#include "../Enum/enum_helper_pub.h"
//strings asociated with enum
#include "../Enum/enum_helper_pri.h"
};
#undef STATICFIELDGETTER
