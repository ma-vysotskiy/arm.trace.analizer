/*
 * Packet.hpp
 *
 *  Created on: Apr 22, 2013
 *      Author: mvis
 */

#pragma once

#include <stdint.h>
#include <vector>
#include <string>
#include <memory>
#include <list>

#include "../Defines.hpp"

class CPacket;
typedef ::std::shared_ptr<CPacket> sharedPacket;
typedef ::std::list<sharedPacket> packetType;

class CPacket {
public:
	CPacket(uint32_t h, dataType d) :
			header(h), data(d) {

	}
	virtual ~CPacket() {
	}
	uint32_t getHeader() {
		return header;
	}
	virtual uint32_t getField(uint32_t enumValue) = 0;
	virtual uint64_t get64Field(uint32_t enumValue) {
		return 0;
	}
	;
	virtual uint32_t getLastField() = 0;
	virtual const fieldStrPair& getFieldStr(uint32_t enumValue) = 0;
protected:
	uint32_t getBits(uint32_t first, uint32_t len);
	uint32_t header;
	dataType data;
private:
	static const uint32_t byteSize = 8;
};

