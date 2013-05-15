#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <stdint.h>
#include "Packet/Data.hpp"
#include <list>

using namespace std;

int main(int argc, char **argv) {
	std::fstream ifs;
	uint32_t ts, value, bits;
	std::string scale;
	ifs.open("test.txt", std::ifstream::in | std::ifstream::out);

	list<CData> rawData;

	while (!ifs.eof()) {
		CData data;
		ifs >> std::dec >> ts;
		ifs >> scale;
		ifs >> std::hex >> value;
		ifs >> bits;
		data.data = value;
		data.ts = ts;
		rawData.push_back(data);
		std::cout << std::dec << ts << " " << scale << " " << std::hex << value
				<< " " << bits << std::endl;
	}

	ifs.close();

	return 0;
}
