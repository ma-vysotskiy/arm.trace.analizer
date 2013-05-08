/*
 * PTMAtomPacket.hpp
 *
 *  Created on: Apr 23, 2013
 *      Author: mvis
 */

#pragma once

#include "../Defines.hpp"
#include "../Packet/PTM/PTMAtomPacket.hpp"
#include "../Exceptions/enumerror.hpp"

class CPTMAtomPacketTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		dataType data;
		data.push_back(CData(0x82, 34));
		data.push_back(CData(0x64, 21));
		data.push_back(CData(0x00, 21));
		data.push_back(CData(0x00, 21));
		data.push_back(CData(0x00, 21));
		packet = new CPTMAtomPacket(0x9e, data);
	}
	virtual void TearDown() {
		delete packet;
	}
	CPTMAtomPacket *packet;
};

TEST_F(CPTMAtomPacketTest, getField) {
	//check exceptions
	ASSERT_THROW(packet->getField(-1), enum_error);
	ASSERT_THROW(packet->getField(CPTMAtomPacket::SIZE), enum_error);
	//check Isync fields count
	EXPECT_EQ(CPTMAtomPacket::SIZE, 2);
	EXPECT_EQ(packet->getLastField(), CPTMAtomPacket::SIZE);
	//check packets content by fields
	EXPECT_EQ(packet->getField(CPTMAtomPacket::F), (uint32_t) 1);
	EXPECT_EQ(packet->getField(CPTMAtomPacket::Count), (uint32_t) 0x640);
}
