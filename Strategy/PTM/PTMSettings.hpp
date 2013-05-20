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
#include "../../Packet/PTM/PTMPackets.hpp"

using namespace std;

class CPTMSimpleOption;
class CPTMComplexOption;

class CPTMSettings : public CStrategySettings {
public:
	void init(string str) {
		settings = CUtils::parseOptions<CPTMSimpleOption, CPTMComplexOption>(
				str);
	}
};
#define STATICFIELDGETTER
#undef enumBody
#define enumBody \
e_begin(field) \
	e_member(CycleCount, %cc) \
	e_member(ContextID, %ci) \
e_end

class CPTMSimpleOption : public CBaseOption {
public:
#include "../../Enum/enum_helper_pub.h"
//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"
};

#undef enumBody
#define enumBody \
e_begin(field) \
	e_member(Output, output) \
e_end

class CPTMComplexOption : public CBaseComplexOption {
public:
	map<string, uint32_t> parseComplex(string opt, string toParse) {
		//scan packets and form output map
		//parse string and flag present opts as enabled, other opts as disabled
	}
#include "../../Enum/enum_helper_pub.h"
//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"
private:
	map<string, uint32_t> parseOutput(string toParse) {
		map<string, uint32_t> output;
		vector<CPacket*> packets = { new CPTMAsyncPacket(0, dataType()),
				new CPTMAtomPacket(0, dataType()), new CPTMBranchPacket(0,
						dataType()), new CPTMContextIDPacket(0, dataType()),
				new CPTMExceptionReturnPacket(0, dataType()),
				new CPTMIgnorePacket(0, dataType()), new CPTMIsyncPacket(0,
						dataType()), new CPTMTimestampPacket(0, dataType()),
				new CPTMTriggerPacket(0, dataType()), new CPTMWaypointPacket(0,
						dataType()) };
		for (uint32_t i = 0; i < packets.size(); ++i) {
			CPacket* packet = packets[i];
			for (uint32_t j = 0; j < packet->getLastField(); ++j) {
				string opt(
						CUtils::enumToString<CPTMComplexOption>(
								CPTMComplexOption::Output) + "_"
								+ packet->getFieldStr(j).first);
				output[opt] = true;
			}
			delete packet;
		}
	}
};

#undef STATICFIELDGETTER
