/*
 * PTMAtomPacket.hpp
 *
 *  Created on: Apr 23, 2013
 *      Author: mvis
 */

#pragma once

#include "../../Defines.hpp"
#include "../../Packet/Packet.hpp"
#include "../../Exceptions/enumerror.hpp"

#undef enumBody
#define enumBody \
e_begin(field) \
	e_member(F, %at) \
	e_member(Count, %cc) \
e_end

class CPTMAtomPacket: public CPacket {

public:
	CPTMAtomPacket(uint32_t h, dataType d) :
			CPacket(h, d) {
	}

	virtual ~CPTMAtomPacket() {
	}

	uint32_t getField(uint32_t enumValue) throw (enum_error) {
		uint32_t result = 0;
		if ((enumValue < 0) || enumValue >= SIZE) {
			throw enum_error();
		}
		switch (enumValue) {
		case F:
			result = getBits(1, 1);
			break;
		case Count:
			result = (getBits(32, 7) << 25) | (getBits(24, 7) << 18)
					| (getBits(16, 7) << 11) | (getBits(8, 7) << 4)
					| (getBits(2, 4) << 0);
			break;
		}
		return result;
	}

	//add enum declaration
#include "../../Enum/enum_helper_pub.h"
	//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"
};
