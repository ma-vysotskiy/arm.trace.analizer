/*
 * PTMTimestampPacket.hpp
 *
 *  Created on: Apr 29, 2013
 *      Author: mvis
 */

#pragma once

#include "../Defines.hpp"
#include "../Packet/PTM/PTMTimestampPacket.hpp"
#include "../Exceptions/enumerror.hpp"

class CPTMTimestampPacketTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		dataType data;
		//timestamp 0x30405060708
		data.push_back(CData(0x88, 0xa1));
		data.push_back(CData(0x8e, 0xa1));
		data.push_back(CData(0x98, 0xa6));
		data.push_back(CData(0xa8, 0xa6));
		data.push_back(CData(0xc0, 0x4c));
		data.push_back(CData(0xe0, 0x4c));
		data.push_back(CData(0x00, 0x4c));
		//cyclecount 0x80907fcc
		data.push_back(CData(0x70, 0x87));
		data.push_back(CData(0xfc, 0x87));
		data.push_back(CData(0x8f, 0x87));
		data.push_back(CData(0xa4, 0x87));
		data.push_back(CData(0x40, 0x0));
		packet = new CPTMTimestampPacket(0x72, data);
	}
	virtual void TearDown() {
		delete packet;
	}
	CPTMTimestampPacket *packet;
};

TEST_F (CPTMTimestampPacketTest, getField) {
	//check exceptions
	ASSERT_THROW(packet->getField(-1), enum_error);
	ASSERT_THROW(packet->getField(CPTMTimestampPacket::SIZE), enum_error);
	//check Branch fields count
	EXPECT_EQ(CPTMTimestampPacket::SIZE, 2);
	EXPECT_EQ(packet->get64Field(CPTMTimestampPacket::Timestamp), (uint64_t)0x30405060708);
	EXPECT_EQ(packet->getField(CPTMTimestampPacket::CycleCount), (uint32_t)0x80907fcc);
}
