/*
 * PTMTimestampPacket.hpp
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
	e_member(Timestamp, %ts) \
	e_member(CycleCount, %cc) \
e_end

class CPTMTimestampPacket: public CPacket {

public:
	CPTMTimestampPacket(uint32_t h, dataType d) :
			CPacket(h, d) {
	}

	virtual ~CPTMTimestampPacket() {
	}

	uint32_t getField(uint32_t enumValue) throw (enum_error) {
		uint32_t result = 0;
		if ((enumValue < 0) || enumValue >= SIZE) {
			throw enum_error();
		}
		switch (enumValue) {
		case CycleCount:
			result = (getBits(88, 7) << 25) | (getBits(80, 7) << 18)
					| (getBits(72, 7) << 11) | (getBits(64, 7) << 4)
					| getBits(58, 4);
			break;
		}
		return result;
	}
	uint64_t get64Field(uint32_t enumValue) throw (enum_error) {
		uint64_t result = 0;
		if ((enumValue < 0) || enumValue >= SIZE) {
			throw enum_error();
		}
		switch (enumValue) {
		case Timestamp:
			result = (((uint64_t) getBits(48, 6)) << 42)
					| (((uint64_t) getBits(40, 7)) << 35)
					| (((uint64_t) getBits(32, 7)) << 28)
					| (((uint64_t) getBits(24, 7)) << 21)
					| (((uint64_t) getBits(16, 7)) << 14)
					| (((uint64_t) getBits(8, 7)) << 7)
					| (((uint64_t) getBits(0, 7)) << 0);
			break;
		}
		return result;
	}

	//add enum declaration
#include "../../Enum/enum_helper_pub.h"
	//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"
};
