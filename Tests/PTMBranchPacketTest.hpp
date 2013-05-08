/*
 * PTMBranchPacketTest.hpp
 *
 *  Created on: Apr 29, 2013
 *      Author: mvis
 */

#pragma once

#include "../Defines.hpp"
#include "../Packet/PTM/PTMBranchPacket.hpp"
#include "../Exceptions/enumerror.hpp"

class CPTMBranchPacketTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		dataType data;
		//address
		data.push_back(CData(0xa1, 0xa1));
		data.push_back(CData(0xa1, 0xa1));
		data.push_back(CData(0xa6, 0xa6));
		data.push_back(CData(0xad, 0xa6));
		data.push_back(CData(0x4c, 0x4c));
		//exception[0:3] 0011  NS 1
		data.push_back(CData(0x87, 0x87));
		data.push_back(CData(0x0, 0x0));
		//cyclecount 0xa0b0c0e0
		data.push_back(CData(0x40, 0xbc));
		data.push_back(CData(0x8e, 0x8e));
		data.push_back(CData(0x98, 0x98));
		data.push_back(CData(0xac, 0xac));
		data.push_back(CData(0x50, 0x50));
		packet = new CPTMBranchPacket(0x81, data);
		packet->instrSetCurrState = CPTMBranchPacket::ARM;
	}
	virtual void TearDown() {
		delete packet;
	}
	CPTMBranchPacket *packet;
};

TEST_F (CPTMBranchPacketTest, getField) {
	//check exceptions
	ASSERT_THROW(packet->getField(-1), enum_error);
	ASSERT_THROW(packet->getField(CPTMBranchPacket::SIZE), enum_error);
	//check Branch fields count
	EXPECT_EQ(CPTMBranchPacket::SIZE, 5);
	EXPECT_EQ(packet->getField(CPTMBranchPacket::Address), (uint32_t)0x8b532140);
	EXPECT_EQ(packet->getField(CPTMBranchPacket::NS), (uint32_t)1);
	EXPECT_EQ(packet->getField(CPTMBranchPacket::Exception), (uint32_t)3);
	EXPECT_EQ(packet->getField(CPTMBranchPacket::AltIS), (uint32_t)0);
	EXPECT_EQ(packet->getField(CPTMBranchPacket::CycleCount), (uint32_t)0xa0b0c0e0);
}
