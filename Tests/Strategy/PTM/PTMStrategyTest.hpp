/*
 * PTMStrategyTest.hpp
 *
 *  Created on: May 22, 2013
 *      Author: mvis
 */

#pragma once

#include "../../../Defines.hpp"
#include "../../../Packet/Packet.hpp"
#include "../../../Packet/Data.hpp"
#include "../../../Packet/PTM/PTMPackets.hpp"
#include "../../../Strategy/PTM/PTMStrategy.hpp"

class CPTMStrategyTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		CData zerodata(0, 0);
		data = {
			// Async
			zerodata, zerodata, zerodata, zerodata, zerodata,
			// Isync
			CData(0x08,0x0), CData(0x054,0x0), CData(0x60,0x0), CData(0x70,0x0),
			CData(0x80,0x0), CData(0x01,0x0), CData(0xd0,0x0), CData(0xb5,0x0),
			CData(0xc8,0x0), CData(0xcc,0x0), CData(0x10,0x0) , CData(0x20,0x0),
			CData(0x30,0x0), CData(0x55,0x0), CData(0x69,0x0)};
	}

	virtual void TearDown() {

	}
	CPTMStrategy strategy;
	dataType data;
};

TEST_F(CPTMStrategyTest, testPTMStrategy) {
	packetType packets = strategy.parse(data);
	EXPECT_EQ(packets.size(), (uint32_t)2);
	packetType::iterator it = packets.begin();
	it++;
	// second packet is Isync
	EXPECT_EQ((*it)->getField(CPTMIsyncPacket::T), (uint32_t)0x0);
	EXPECT_EQ((*it)->getField(CPTMIsyncPacket::Address), (uint32_t)0x80706054);
	EXPECT_EQ((*it)->getField(CPTMIsyncPacket::AltIS), (uint32_t)0x0);
	EXPECT_EQ((*it)->getField(CPTMIsyncPacket::NS), (uint32_t)0x0);
	EXPECT_EQ((*it)->getField(CPTMIsyncPacket::Reason), (uint32_t)0x0);
	EXPECT_EQ((*it)->getField(CPTMIsyncPacket::CycleCount), (uint32_t)0x21324354);
	EXPECT_EQ((*it)->getField(CPTMIsyncPacket::ContextID), (uint32_t)0x69553020);
}
