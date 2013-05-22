/*
 * Defines.hpp
 *
 *  Created on: Apr 23, 2013
 *      Author: mvis
 */

#pragma once

#include <vector>
#include <list>
#include <map>
#include <string>
#include <stdint.h>
#include "Packet/Data.hpp"
#include "Packet/Packet.hpp"

typedef std::vector<CData> dataType;
typedef std::list<CPacket> packetType;
typedef std::pair<std::string, std::string> fieldStrPair;
typedef std::map<std::string, uint32_t> settingsType;

// String defines used in various packets
//e_member(T, %thu)
//e_member(Address, %a)
//e_member(AltIS, %ai)
//e_member(NS, %ns)
//e_member(Reason, %r)
//e_member(CycleCount, %cc)
//e_member(ContexID, %ci)

