/*
 * testMain.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: mvis
 */

#include "Tests/PTMTests.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
