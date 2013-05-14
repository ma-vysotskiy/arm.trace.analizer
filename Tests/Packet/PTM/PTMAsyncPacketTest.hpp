/*
 * PTMAsyncPacketTest.hpp
 *
 *  Created on: Apr 23, 2013
 *      Author: mvis
 */

#pragma once

#include "../../../Defines.hpp"
#include "../../../Packet/PTM/PTMAsyncPacket.hpp"
#include "../../../Exceptions/enumerror.hpp"

class CPTMAsyncPacketTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		dataType data;
		data.push_back(CData(0x0, 34));
		data.push_back(CData(0x0, 21));
		data.push_back(CData(0x0, 21));
		data.push_back(CData(0x0, 21));
		data.push_back(CData(0x0, 21));
		packet = new CPTMAsyncPacket(0x0, data);
	}
	virtual void TearDown() {
		delete packet;
	}
	CPTMAsyncPacket *packet;
};

TEST_F (CPTMAsyncPacketTest, getField) {
	//check exceptions
	ASSERT_THROW(packet->getField(0), enum_error);
	ASSERT_THROW(packet->getField(CPTMAsyncPacket::SIZE), enum_error);
	//check Async have no fields in enum
	EXPECT_EQ(CPTMAsyncPacket::SIZE, 0);
}
