/*
 * PTMBranchPacket.hpp
 *
 *  Created on: Apr 29, 2013
 *      Author: mvis
 */

#pragma once

#include "../../Defines.hpp"
#include "../../Packet/Packet.hpp"
#include "../../Exceptions/enumerror.hpp"

#undef enumBody
#define enumBody \
e_begin(field) \
	e_member(Address, %a) \
	e_member(NS, %ns) \
	e_member(Exception, %ex) \
	e_member(AltIS, %ai) \
	e_member(CycleCount, %cc) \
e_end

class CPTMBranchPacket: public CPacket {

public:
	CPTMBranchPacket(uint32_t h, dataType d) :
			CPacket(h, d), instrSetCurrState(ARM) {
	}

	virtual ~CPTMBranchPacket() {
	}

	uint32_t getField(uint32_t enumValue) throw (enum_error) {
		uint32_t result = 0;
		if ((enumValue < 0) || enumValue >= SIZE) {
			throw enum_error();
		}
		switch (enumValue) {
		case Address:
			result = (getBits(32, 5 - instrSetCurrState)
					<< (27 + instrSetCurrState))
					| (getBits(24, 7) << (20 + instrSetCurrState))
					| (getBits(16, 7) << (13 + instrSetCurrState))
					| (getBits(8, 7) << (6 + instrSetCurrState))
					| (getBits(1, 6) << instrSetCurrState);
			break;
		case NS:
			result = getBits(40, 1);
			break;
		case Exception:
			result = (getBits(48, 4) << 4) | getBits(41, 4);
			break;
		case AltIS:
			result = getBits(46, 1);
			break;
		case CycleCount:
			result = (getBits(88, 7) << 25) | (getBits(80, 7) << 18)
					| (getBits(72, 7) << 11) | (getBits(64, 7) << 4)
					| (getBits(58, 4) << 0);
			break;
		}
		return result;
	}

	enum state {
		JAZELLE = 0, THUMB = 1, ARM = 2,
	};
	//make state accessible from ptm strategy settings
	state instrSetCurrState;
	//add enum declaration
#include "../../Enum/enum_helper_pub.h"
	//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"
};
