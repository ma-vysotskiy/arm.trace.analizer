/*
 * PTMContextIDPacketTest.hpp
 *
 *  Created on: Apr 29, 2013
 *      Author: mvis
 */

#pragma once

#include "../Defines.hpp"
#include "../Packet/PTM/PTMContextIDPacket.hpp"
#include "../Exceptions/enumerror.hpp"

class CPTMContextIDPacketTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		dataType data;
		//contextid
		data.push_back(CData(0xa1, 0xa1));
		data.push_back(CData(0xa6, 0xa6));
		data.push_back(CData(0xad, 0xa6));
		data.push_back(CData(0x4c, 0x4c));
		packet = new CPTMContextIDPacket(0x6e, data);
	}
	virtual void TearDown() {
		delete packet;
	}
	CPTMContextIDPacket *packet;
};

TEST_F (CPTMContextIDPacketTest, getField) {
	//check exceptions
	ASSERT_THROW(packet->getField(-1), enum_error);
	ASSERT_THROW(packet->getField(CPTMContextIDPacket::SIZE), enum_error);
	//check Branch fields count
	EXPECT_EQ(CPTMContextIDPacket::SIZE, 1);
	EXPECT_EQ(packet->getField(CPTMContextIDPacket::ContextID), (uint32_t)0x4cada6a1);
}
