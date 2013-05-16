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
#include "../../Packet/PTM/PTMIsyncPacket.hpp"
#include "../../Strategy/GlobalSettings.hpp"
#include "../../Common/Utils.hpp"

using namespace std;

class CPTMSettings : public CStrategySettings {
public:
	void init(string str) {
		settings[CUtils::enumToString<CPTMIsyncPacket>(
				CPTMIsyncPacket::CycleCount)] = false;
		settings[CUtils::enumToString<CPTMIsyncPacket>(
				CPTMIsyncPacket::ContextID)] = false;
		// ARM STATE? ARM THUMB JAZZELE ?
		// contextidsize (for contextid packet)
		string opt = CUtils::enumToString<CGlobalSettings>(
				CGlobalSettings::Output);
		pair<string, string> res = CUtils::getInternalOptions(str, opt);
		str = res.first;
	}
};
