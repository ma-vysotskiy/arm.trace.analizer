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
			CData(0x08,0x0), CData(0x54,0x0), CData(0x60,0x0), CData(0x70,0x0),
			CData(0x80,0x0), CData(0x01,0x0), CData(0xd0,0x0), CData(0xb5,0x0),
			CData(0xc8,0x0), CData(0xcc,0x0), CData(0x10,0x0), CData(0x20,0x0),
			CData(0x30,0x0), CData(0x55,0x0), CData(0x69,0x0),
			// waypoint up
			CData(0x72,0x0), CData(0x9f,0x0), CData(0xa1,0x0), CData(0xc8,0x0),
			CData(0xda,0x0), CData(0x4a,0x0), CData(0x00,0x0),
			// trigger
			CData(0x0c,0x0),
			// context id
			CData(0x6e,0x0), CData(0x6e,0x0), CData(0xe6,0x0), CData(0x77,0x0),
			CData(0x66,0x0),
			// timestamp
			CData(0x42,0x0), CData(0x87,0x0), CData(0x8c,0x0), CData(0x94,0x0),
			CData(0xa0,0x0), CData(0xb0,0x0), CData(0xc0,0x0), CData(0xc0,0x0),

			CData(0x50,0x0), CData(0xd0,0x0), CData(0xc0,0x0), CData(0xc1,0x0),
			CData(0x83,0x0),
		};
		strategy.setSettings("cis=\"4\" %cc %ci");
	}

	virtual void TearDown() {

	}
	CPTMStrategy strategy;
	dataType data;
};

TEST_F(CPTMStrategyTest, testPTMStrategy) {
	packetType packets = strategy.parse(data);
	EXPECT_EQ(packets.size(), (uint32_t)6);
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
	it++;
	// third packet is Waypoint up
	EXPECT_EQ((*it)->getField(CPTMWaypointPacket::Address), (uint32_t)0x56a4213c);
	EXPECT_EQ((*it)->getField(CPTMWaypointPacket::AltIS), (uint32_t)0x0);
	it++;
	// forth packet is trigger
	EXPECT_EQ((*it)->getHeader(), (uint32_t)0x0c);
	it++;
	// fifth packet is contextid
	EXPECT_EQ((*it)->getField(CPTMContextIDPacket::ContextID), (uint32_t)0x6677e66e);
	it++;
	// sixth packet is timestamp
	EXPECT_EQ((*it)->get64Field(CPTMTimestampPacket::Timestamp), (uint64_t)0x020304050607);
	EXPECT_EQ((*it)->getField(CPTMTimestampPacket::CycleCount), (uint32_t)0x07060504);
}
