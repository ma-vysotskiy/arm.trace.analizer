/*
 * notfounderror.hpp
 *
 *  Created on: May 17, 2013
 *      Author: mvis
 */

#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class notfound_error: public runtime_error {
public:
	notfound_error() :
			runtime_error("not found error") {
	}
	notfound_error(const std::string& what_arg) :
			runtime_error(what_arg) {
	}
	virtual ~notfound_error() noexcept(true) {
	}
};
