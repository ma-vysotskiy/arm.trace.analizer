/*
 * PTMSettings.hpp
 *
 *  Created on: May 13, 2013
 *      Author: mvis
 */

#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#include "../../../Defines.hpp"
#include "../../../Common/Utils.hpp"
#include "../../../Strategy/PTM/PTMSettings.hpp"
#include "../../../Strategy/Settings.hpp"

class CPTMSettingsTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		settings.init("");
	}

	virtual void TearDown() {

	}
	CPTMSettings settings;
	CPTMComplexOption complexOpt;
};

TEST_F(CPTMSettingsTest, testSettings) {

	//check default values of this options
	EXPECT_EQ(settings.get(CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::CycleCount)),(uint32_t) 0);
	EXPECT_EQ(settings.get(CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::ContextID)),(uint32_t) 0);
	//check that options changed
	settings.init("%cc %ci");
	EXPECT_EQ(settings.get(CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::CycleCount)),(uint32_t) 1);
	EXPECT_EQ(settings.get(CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::ContextID)),(uint32_t) 1);
}


TEST_F (CPTMSettingsTest, testPTMComplexOptions) {
	string optName = CUtils::enumToString<CPTMComplexOption>(
			CPTMComplexOption::Output);
	string cc = CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::CycleCount);
	string ci = CUtils::enumToString<CPTMIsyncPacket>(CPTMIsyncPacket::ContextID);
	string a = CUtils::enumToString<CPTMBranchPacket>(CPTMBranchPacket::Address);
	string ex = CUtils::enumToString<CPTMBranchPacket>(CPTMBranchPacket::Exception);
	string ns = CUtils::enumToString<CPTMBranchPacket>(CPTMBranchPacket::NS);
	settingsType map = complexOpt.parseComplex(optName, "%cc %ci %a %ex");
	EXPECT_EQ(map[optName + "_" + cc],(uint32_t) 1);
	EXPECT_EQ(map[optName + "_" + ci],(uint32_t) 1);
	EXPECT_EQ(map[optName + "_" + a],(uint32_t) 1);
	EXPECT_EQ(map[optName + "_" + ex],(uint32_t) 1);
	EXPECT_EQ(map[optName + "_" + ns],(uint32_t) 0);
}

