/*
 * PTMSettings.hpp
 *
 *  Created on: May 13, 2013
 *      Author: mvis
 */

#pragma once
#include <iostream>
using namespace std;
#include "../../../Defines.hpp"
#include "../../../Common/Utils.hpp"
#include "../../../Strategy/PTM/PTMSettings.hpp"
#include "../../../Strategy/GlobalSettings.hpp"

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
	EXPECT_EQ(settings.get(CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::CycleCount)),(uint32_t) 0);
	EXPECT_EQ(settings.get(CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::ContextID)),(uint32_t) 0);
	//check that options changed
	settings.init("-cc -ci");
	EXPECT_EQ(settings.get(CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::CycleCount)),(uint32_t) 1);
	EXPECT_EQ(settings.get(CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::ContextID)),(uint32_t) 1);
}
