/*
 * PTMAsyncPacket.hpp
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
e_end

class CPTMAsyncPacket: public CPacket {

public:
	CPTMAsyncPacket(uint32_t h, dataType d) :
			CPacket(h, d) {
	}

	virtual ~CPTMAsyncPacket() {
	}

	uint32_t getField(uint32_t enumValue) throw (enum_error) {
		if ((enumValue < 0) || enumValue >= SIZE) {
			throw enum_error();
		}
		return 0;
	}

	//add enum declaration
#include "../../Enum/enum_helper_pub.h"
	//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"
};

