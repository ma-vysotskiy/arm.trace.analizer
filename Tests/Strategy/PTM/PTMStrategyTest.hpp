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
		dataType data = {};
	}

	virtual void TearDown() {

	}
	CPTMStrategy strategy;
}

TEST_F(CPTMStrategyTest, testPTMStrategy) {

}
