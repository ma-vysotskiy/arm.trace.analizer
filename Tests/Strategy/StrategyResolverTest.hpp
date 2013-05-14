/*
 * StrategyResolverTest.hpp
 *
 *  Created on: May 14, 2013
 *      Author: mvis
 */

#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../Strategy/StrategyResolver.hpp"

class CStrategyResolverTest : public ::testing::Test {
protected:
	virtual void SetUp() {
	}
	virtual void TearDown() {
	}
};

TEST_F (CStrategyResolverTest, initTest) {
	CStrategyResolver& resolver = CStrategyResolver::getInstance();
	resolver.init(" la la la PTM=\"dasdadas output=\"asda\"\"");
}
