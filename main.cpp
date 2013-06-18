#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <stdint.h>
#include <list>

#include "Packet/Data.hpp"
#include "Parser.hpp"
#include "Strategy/StrategyResolver.hpp"
#include "Exceptions/notenoughdata.hpp"
using namespace std;

int main(int argc, char **argv) {
	std::fstream ifs;
	CParser& parser = CParser::getInstance();
	string opts;
	cout << "Start" << endl;
	if (argc >= 2) {
		for (uint32_t i = 2; i < argc; i++) {
			opts = opts + " " + argv[i];
		}
		ifs.open(argv[1], std::ifstream::in | std::ifstream::out);
		CStrategyResolver::getInstance().init(opts);
		try {
			parser.parse(ifs, 16);
		} catch (notenough_data& e) {
			cout << "Exception! " << e.what() << endl;
		}

		ifs.close();
	}
	return 0;
}
