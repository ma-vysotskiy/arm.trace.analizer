/*
 * PTMWaypointPacketTest.hpp
 *
 *  Created on: Apr 29, 2013
 *      Author: mvis
 */

#pragma once

#include "../../../Defines.hpp"
#include "../../../Packet/PTM/PTMWaypointPacket.hpp"
#include "../../../Exceptions/enumerror.hpp"

class CPTMWaypointPacketTest: public ::testing::Test {
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
		packet = new CPTMWaypointPacket(0x72, data);
		packet->instrSetCurrState = CPTMWaypointPacket::ARM;
	}
	virtual void TearDown() {
		delete packet;
	}
	CPTMWaypointPacket *packet;
};

TEST_F (CPTMWaypointPacketTest, getField) {
	//check exceptions
	ASSERT_THROW(packet->getField(-1), enum_error);
	ASSERT_THROW(packet->getField(CPTMWaypointPacket::SIZE), enum_error);
	//check Branch fields count
	EXPECT_EQ(CPTMWaypointPacket::SIZE, 2);
	EXPECT_EQ(packet->getField(CPTMWaypointPacket::Address), (uint32_t)0x8b532140);
	EXPECT_EQ(packet->getField(CPTMWaypointPacket::AltIS), (uint32_t)0);
}
