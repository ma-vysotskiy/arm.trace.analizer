/*
 * PTMTriggerPacketTest.hpp
 *
 *  Created on: Apr 29, 2013
 *      Author: mvis
 */

#pragma once

#include "../Defines.hpp"
#include "../Packet/PTM/PTMTriggerPacket.hpp"
#include "../Exceptions/enumerror.hpp"

class CPTMTriggerPacketTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		dataType data;
		//address
		data.push_back(CData(0xa1, 0xa1));
		data.push_back(CData(0xa1, 0xa1));
		data.push_back(CData(0xa6, 0xa6));
		data.push_back(CData(0xad, 0xa6));
		data.push_back(CData(0x4c, 0x4c));
		//AltIS 0
		data.push_back(CData(0x87, 0x87));
		data.push_back(CData(0x0, 0x0));
		packet = new CPTMTriggerPacket(0x72, data);
	}
	virtual void TearDown() {
		delete packet;
	}
	CPTMTriggerPacket *packet;
};

TEST_F (CPTMTriggerPacketTest, getField) {
	//check exceptions
	ASSERT_THROW(packet->getField(-1), enum_error);
	ASSERT_THROW(packet->getField(CPTMTriggerPacket::SIZE), enum_error);
	//check Branch fields count
	EXPECT_EQ(CPTMTriggerPacket::SIZE, 0);
}
