/*
 * PTMSettings.hpp
 *
 *  Created on: May 8, 2013
 *      Author: mvis
 */

#pragma once

#include "../../Defines.hpp"
#include "../../Strategy/StrategySettings.hpp"
#include "../../Packet/PTM/PTMIsyncPacket.hpp"
#include "../../Packet/FieldToString.hpp"


class CPTMSettings : public CStrategySettings {
public:
	void init(string str) {
		settings[CFieldToString::get<CPTMIsyncPacket>(CPTMIsyncPacket::CycleCount)]=false;
		settings[CFieldToString::get<CPTMIsyncPacket>(CPTMIsyncPacket::ContextID)]=false;
		// ARM STATE? ARM THUMB JAZZELE ?
		// contextidsize (for contextid packet)
	}
};
