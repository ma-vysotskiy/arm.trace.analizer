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
#include "../../Strategy/Settings.hpp"
#include "../../Common/Utils.hpp"

class CStrategyResolverTest : public ::testing::Test {
protected:
	virtual void SetUp() {
	}
	virtual void TearDown() {
	}
};

TEST_F (CStrategyResolverTest, initTest) {
	CStrategyResolver& resolver = CStrategyResolver::getInstance();
	resolver.init(" la %cc la la PTM=\"%t %cc %a output=\"asda\"\"");
//	CUtils::enumToPair<CSimpleOption>(0);
//	CUtils::enumToPair<CComplexSettings>(0);
	throw 0;
}
