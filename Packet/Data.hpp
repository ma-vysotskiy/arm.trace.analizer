/*
 * Data.h
 *
 *  Created on: Apr 22, 2013
 *      Author: mvis
 */

#pragma once

#include <stdint.h>

struct CData {
	CData(){}
	CData(uint8_t data, uint32_t ts) :
			data(data), ts(ts) {

	}
	uint8_t data;
	uint32_t ts;
};
