/*
 * PacketTest.hpp
 *
 *  Created on: Apr 22, 2013
 *      Author: mvis
 */

#pragma once

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>
#include <string>
#include <stdint.h>

#include "../Packet/Packet.hpp"
#include "../Defines.hpp"
#include "../Exceptions/enumerror.hpp"

using namespace std;

#undef enumBody
#define enumBody \
e_begin(field) \
e_end

class CPacketHelp : public CPacket {
public:
	CPacketHelp(uint32_t h, dataType d) :
			CPacket(h, d), p("", "") {

	}
	virtual ~CPacketHelp() {
	}
	uint32_t helpGetBits(uint32_t first, uint32_t len) {
		return getBits(first, len);
	}
	uint32_t getField(uint32_t enumValue) throw (enum_error) {
		if ((enumValue < 0) || enumValue >= SIZE) {
			throw enum_error();
		}
		return 0;
	}
	//add enum declaration
#include "../Enum/enum_helper_pub.h"
	//strings asociated with enum
#include "../Enum/enum_helper_pri.h"

	const fieldStrPair p;
};

class CPacketTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		dataType data;
		data.push_back(CData(0x34, 43));
		data.push_back(CData(0x12, 21));
		packet = new CPacketHelp(0xa0a0a0a0, data);
	}
	virtual void TearDown() {
		delete packet;
	}
	CPacketHelp *packet;
};

TEST_F (CPacketTest, getBits) {
	int testVal = packet->helpGetBits(0,4);
	EXPECT_EQ(testVal,4);
	testVal = packet->helpGetBits(4,4);
	EXPECT_EQ(testVal,3);
	testVal = packet->helpGetBits(1,2);
	EXPECT_EQ(testVal,2);
	testVal = packet->helpGetBits(5,8);
	EXPECT_EQ(testVal,0x91);
}
