/*
 * Utils.hpp
 *
 *  Created on: May 15, 2013
 *      Author: mvis
 */

#pragma once

#include <string>
#include <stack>

#include "../Defines.hpp"
#include "../Strategy/GlobalSettings.hpp"

using namespace std;

class CUtils {
public:
	static pair<string, string> getInternalOptions(string str, string what) {
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

		string newStr = str.erase(pos, result.size() + 3 + what.size());

		return make_pair(newStr, result);
	}

	template<typename T>
	inline static string enumToString(uint32_t enumValue);

};

template<typename T>
inline string CUtils::enumToString(uint32_t enumValue) {
	T obj(0, dataType());
	return obj.getFieldStr(enumValue).first;
}

template<>
inline string CUtils::enumToString<CGlobalSettings>(uint32_t enumValue) {
	CGlobalSettings& obj = CGlobalSettings::getInstance();
	return obj.getFieldStr(enumValue).first;
}
