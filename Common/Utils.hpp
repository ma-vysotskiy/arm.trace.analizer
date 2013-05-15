/*
 * Utils.hpp
 *
 *  Created on: May 15, 2013
 *      Author: mvis
 */

#pragma once

#include <string>

using namespace std;

class CUtils {
public:
	static string getInternalOptions(string str, string what) {
		uint32_t pos = str.find(what + "=\"", 0);
		string::iterator it = str.begin();
		it += pos + what.size() + 2;
		string::iterator start = it;
		stack<char> st;
		string result = "";
		while (it != str.end()) {
			string::iterator next = it + 1;
			if ((*it) == '=' && (*next) == '\"') {
				st.push('"');
				it++;
			} else if ((*it) == '\"') {
				if (st.empty()) {
					result = string(start, it);
					break;
				} else {
					st.pop();
				}
			}
			it++;
		}
		return result;
	}
};
