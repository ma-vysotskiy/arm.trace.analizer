/*
 * Utils.hpp
 *
 *  Created on: May 15, 2013
 *      Author: mvis
 */

#pragma once

#include <string>
#include <stack>

#include <boost/regex.hpp>

#include "../Defines.hpp"
#include "../Strategy/Settings.hpp"
#include "../Exceptions/notfounderror.hpp"

using namespace std;

class CUtils {
public:

	static map<string,uint32_t> parseOptions(string str){
		map<string, uint32_t> settings;
		settings[CUtils::enumToString<CPTMIsyncPacket>(
				CPTMIsyncPacket::CycleCount)] = false;
		settings[CUtils::enumToString<CPTMIsyncPacket>(
				CPTMIsyncPacket::ContextID)] = false;
		// ARM STATE? ARM THUMB JAZZELE ?
		// contextidsize (for contextid packet)
		string opt = CUtils::enumToPair<CComplexSettings>(
				CComplexSettings::Output).second;
		try {
			pair<string, string> res = CUtils::getInternalOptions(str, opt);
			str = res.first;
			opt = CUtils::enumToPair<CPTMIsyncPacket>(
					CPTMIsyncPacket::CycleCount).second;
			boost::regex e(opt);
			boost::match_results<std::string::const_iterator> what;
			bool x = 0;
			if (x = boost::regex_search(str, what, e)) {
				settings[opt] = true;
			}
		} catch (notfound_error &e) {
			//
		}
		return settings;
	}

	static pair<string, string> getInternalOptions(string str, string what)
			throw (notfound_error) {
		uint32_t pos = str.find(what + "=\"", 0);
		if (pos == string::npos) {
			throw notfound_error();
		}
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
		string newStr = str;
		try {
			newStr = str.erase(pos, result.size() + 3 + what.size());
		} catch (...) {
		}
		return make_pair(newStr, result);
	}

	template<typename T>
	inline static string enumToString(uint32_t enumValue);

	template<typename T>
	inline static pair<string, string> enumToPair(uint32_t enumValue);

};

template<typename T>
inline pair<string, string> CUtils::enumToPair(uint32_t enumValue) {
	T obj(0, dataType());
	return obj.getFieldStr(enumValue);
}

template<>
inline pair<string, string> CUtils::enumToPair<CSimpleSettings>(
		uint32_t enumValue) {
	CSimpleSettings obj(0, dataType());
	return obj.getFieldStr(enumValue);
}

template<typename T>
inline string CUtils::enumToString(uint32_t enumValue) {
	return CUtils::enumToPair<T>(enumValue).first;
}

