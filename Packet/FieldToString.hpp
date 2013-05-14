/*
 * FieldToString.hpp
 *
 *  Created on: May 13, 2013
 *      Author: mvis
 */

#pragma once

#include <string>
#include <stdint.h>

using namespace std;

class CFieldToString {
public:
	template<typename T>
	static string get(uint32_t enumValue){
		T obj(0, dataType());
		return obj.getFieldStr(enumValue).first;
	}
};
