/*
 * Defines.hpp
 *
 *  Created on: Apr 23, 2013
 *      Author: mvis
 */

#pragma once

#include <vector>
#include "Packet/Data.hpp"

using namespace std;

typedef vector<CData> dataType;
typedef std::pair<std::string, std::string> fieldStrPair;

// String defines used in various packets
//e_member(T, %thu)
//e_member(Address, %a)
//e_member(AltIS, %ai)
//e_member(NS, %ns)
//e_member(Reason, %r)
//e_member(CycleCount, %cc)
//e_member(ContexID, %ci)

#define GETLASTFIELD	uint32_t getLastField() noexcept { \
		return SIZE; \
}

#define GETFIELDSTR		const fieldStrPair& getFieldStr(uint32_t enumValue) throw (enum_error) { \
	if ((enumValue < 0) || enumValue >= SIZE) { \
		throw enum_error(); \
	} \
	return field_s(enumValue); \
}
