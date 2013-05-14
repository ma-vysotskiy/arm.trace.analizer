/*
 * PTMIsyncPacketTest.hpp
 *
 *  Created on: Apr 23, 2013
 *      Author: mvis
 */

#pragma once

#include "../../../Defines.hpp"
#include "../../../Packet/PTM/PTMIsyncPacket.hpp"
#include "../../../Exceptions/enumerror.hpp"

class CPTMIsyncPacketTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		dataType data;
		data.push_back(CData(0xf6, 34));
		data.push_back(CData(0xb0, 21));
		data.push_back(CData(0x7a, 21));
		data.push_back(CData(0x98, 21));
		data.push_back(CData(0x29, 21));
		data.push_back(CData(0x1c, 21));
		data.push_back(CData(0x07, 21));
		data.push_back(CData(0x0, 21));
		data.push_back(CData(0x0, 21));
		data.push_back(CData(0x33, 21));
		data.push_back(CData(0xbb, 21));
		data.push_back(CData(0x45, 21));
		data.push_back(CData(0x12, 21));
		packet = new CPTMIsyncPacket(0x08, data);

		dataType data2;
		data2.push_back(CData(0xf7, 34));
		data2.push_back(CData(0xb0, 21));
		data2.push_back(CData(0x7a, 21));
		data2.push_back(CData(0x98, 21));
		data2.push_back(CData(0x45, 21));
		data2.push_back(CData(0x1c, 21));
		data2.push_back(CData(0x07, 21));
		data2.push_back(CData(0x0, 21));
		data2.push_back(CData(0x0, 21));
		data2.push_back(CData(0x33, 21));
		data2.push_back(CData(0xbb, 21));
		data2.push_back(CData(0x45, 21));
		data2.push_back(CData(0x12, 21));
		packet2 = new CPTMIsyncPacket(0x08, data2);
	}
	virtual void TearDown() {
		delete packet;
		delete packet2;
	}
	CPTMIsyncPacket *packet;
	CPTMIsyncPacket *packet2;
};

TEST_F (CPTMIsyncPacketTest, getField) {
	//check exceptions
	ASSERT_THROW(packet->getField(-1), enum_error);
	ASSERT_THROW(packet->getField(CPTMIsyncPacket::SIZE), enum_error);
	//check Isync fields count
	EXPECT_EQ(CPTMIsyncPacket::SIZE, 7);
	EXPECT_EQ(packet->getLastField(), CPTMIsyncPacket::SIZE);
	//check packets content by fields
	EXPECT_EQ(packet->getField(CPTMIsyncPacket::T), (uint32_t)0);
	EXPECT_EQ(packet->getField(CPTMIsyncPacket::Address), (uint32_t)0x987ab0f6);
	EXPECT_EQ(packet->getField(CPTMIsyncPacket::AltIS), (uint32_t)0);
	EXPECT_EQ(packet->getField(CPTMIsyncPacket::NS), (uint32_t)1);
	EXPECT_EQ(packet->getField(CPTMIsyncPacket::Reason), (uint32_t)1);
	EXPECT_EQ(packet->getField(CPTMIsyncPacket::CycleCount), (uint32_t)0x77);
	EXPECT_EQ(packet->getField(CPTMIsyncPacket::ContextID), (uint32_t)0x1245bb33);

	EXPECT_EQ(packet2->getField(CPTMIsyncPacket::T), (uint32_t)1);
	EXPECT_EQ(packet2->getField(CPTMIsyncPacket::Address), (uint32_t)0x987ab0f6);
	EXPECT_EQ(packet2->getField(CPTMIsyncPacket::AltIS), (uint32_t)1);
	EXPECT_EQ(packet2->getField(CPTMIsyncPacket::NS), (uint32_t)0);
	EXPECT_EQ(packet2->getField(CPTMIsyncPacket::Reason), (uint32_t)2);
	EXPECT_EQ(packet2->getField(CPTMIsyncPacket::CycleCount), (uint32_t)0x77);
	EXPECT_EQ(packet2->getField(CPTMIsyncPacket::ContextID), (uint32_t)0x1245bb33);
}
