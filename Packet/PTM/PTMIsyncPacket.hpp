/*
 * PTMIsyncPacket.hpp
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
	e_member(T, %thu) \
	e_member(Address, %a) \
	e_member(AltIS, %ai) \
	e_member(NS, %ns) \
	e_member(Reason, %r) \
	e_member(CycleCount, %cc) \
	e_member(ContextID, %ci) \
e_end

class CPTMIsyncPacket: public CPacket {

public:
	CPTMIsyncPacket(uint32_t h, dataType d) :
			CPacket(h, d) {
	}

	virtual ~CPTMIsyncPacket() {
	}

	uint32_t getField(uint32_t enumValue) throw (enum_error) {
		uint32_t result = 0;
		if ((enumValue < 0) || enumValue >= SIZE) {
			throw enum_error();
		}
		switch (enumValue) {
		case T:
			result = getBits(0, 1);
			break;
		case Address:
			result = (getBits(8, 24) << 8) | (getBits(1, 7) << 1);
			break;
		case AltIS:
			result = getBits(34, 1);
			break;
		case NS:
			result = getBits(35, 1);
			break;
		case Reason:
			result = getBits(37, 2);
			break;
		case CycleCount:
			result = (getBits(48, 7) << 4)| (getBits(42, 4) << 0);
			break;
		case ContextID:
			result = getBits(72, 32);
			break;
		}
		return result;
	}

	//add enum declaration
#include "../../Enum/enum_helper_pub.h"
private:
	//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"

};
