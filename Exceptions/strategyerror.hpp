/*
 * strategy_error.hpp
 *
 *  Created on: May 17, 2013
 *      Author: mvis
 */

#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class strategy_error: public runtime_error {
public:
	strategy_error() :
			runtime_error("no such strategy") {
	}
	strategy_error(const std::string& what_arg) :
			runtime_error(what_arg) {
	}
	virtual ~strategy_error() noexcept(true) {
	}
};
