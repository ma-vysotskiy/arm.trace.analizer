/*
 * notenoughdata.hpp
 *
 *  Created on: May 28, 2013
 *      Author: mvis
 */

#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class notenough_data: public runtime_error {
public:
	notenough_data() :
			runtime_error("not enough data") {
	}
	notenough_data(const std::string& what_arg) :
			runtime_error(what_arg) {
	}
	virtual ~notenough_data() noexcept(true) {
	}
};
