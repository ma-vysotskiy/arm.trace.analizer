/*
 * PTMContextIDPacket.hpp
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
	e_member(ContextID, %ci) \
e_end

class CPTMContextIDPacket: public CPacket {

public:
	CPTMContextIDPacket(uint32_t h, dataType d) :
			CPacket(h, d) {
	}

	virtual ~CPTMContextIDPacket() {
	}

	uint32_t getField(uint32_t enumValue) throw (enum_error) {
		uint32_t result = 0;
		if ((enumValue < 0) || enumValue >= SIZE) {
			throw enum_error();
		}
		switch (enumValue) {
		case ContextID:
			result = getBits(0, 32);
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
