/*
 * PTMSettings.hpp
 *
 *  Created on: May 13, 2013
 *      Author: mvis
 */

#pragma once

#include "../../../Defines.hpp"
#include "../../../Strategy/PTM/PTMSettings.hpp"

class CPTMSettingsTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		settings.init("");
	}

	virtual void TearDown() {

	}
	CPTMSettings settings;
};

TEST_F(CPTMSettingsTest, getField) {
	//check default values of this options
	EXPECT_EQ(settings.get(CFieldToString::get<CPTMIsyncPacket>(CPTMIsyncPacket::CycleCount)),(uint32_t) 0);
	EXPECT_EQ(settings.get(CFieldToString::get<CPTMIsyncPacket>(CPTMIsyncPacket::ContextID)),(uint32_t) 0);

	//check that options changed
	settings.init("-cc -ci");
	EXPECT_EQ(settings.get(CFieldToString::get<CPTMIsyncPacket>(CPTMIsyncPacket::CycleCount)),(uint32_t) 1);
	EXPECT_EQ(settings.get(CFieldToString::get<CPTMIsyncPacket>(CPTMIsyncPacket::ContextID)),(uint32_t) 1);
}
