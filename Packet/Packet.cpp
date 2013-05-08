/*
 * Data.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: mvis
 */
#include <vector>
#include <algorithm>
#include "../Packet/Packet.hpp"

using namespace std;

uint32_t CPacket::getBits(uint32_t first, uint32_t len) {
	uint32_t result = 0;
	uint32_t startIndex = (uint32_t) (first / byteSize);
	vector<CData>::iterator it = data.begin();
	it += startIndex;
	first -= startIndex * byteSize;
	uint32_t curBit = 0;
	while (len > 0) {
		uint32_t minim = min(len, byteSize - first);
		uint32_t mask = ~(0xffffffff << minim);
		result = result | ((((*it).data >> first) & mask) << curBit);
		curBit += minim;
		len -= minim;
		first = 0;
		it++;
	}
	return result;
}
