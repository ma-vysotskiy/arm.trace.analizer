/*
 * testMain.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: mvis
 */

#include "Tests/PacketTest.hpp"
#include "Tests/PTMTests.hpp"
#include "Tests/ParserTest.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
