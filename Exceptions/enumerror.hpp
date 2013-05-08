/*
 * enumerror.hpp
 *
 *  Created on: Apr 23, 2013
 *      Author: mvis
 */

#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class enum_error: public runtime_error {
public:
	enum_error() :
			runtime_error("no such field") {
	}
	enum_error(const std::string& what_arg) :
			runtime_error(what_arg) {
	}
	virtual ~enum_error() noexcept(true) {
	}
};
