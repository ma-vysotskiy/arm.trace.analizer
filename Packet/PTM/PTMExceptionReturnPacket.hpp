/*
 * PTMExceptionReturnPacket.hpp
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
e_end

class CPTMExceptionReturnPacket: public CPacket {

public:
	CPTMExceptionReturnPacket(uint32_t h, dataType d) :
			CPacket(h, d) {
	}

	virtual ~CPTMExceptionReturnPacket() {
	}

	uint32_t getField(uint32_t enumValue) throw (enum_error) {
		uint32_t result = 0;
		if ((enumValue < 0) || enumValue >= SIZE) {
			throw enum_error();
		}
		return result;
	}

	//add enum declaration
#include "../../Enum/enum_helper_pub.h"
private:
	//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"

};
