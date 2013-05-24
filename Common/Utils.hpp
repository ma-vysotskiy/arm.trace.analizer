/*
 * Utils.hpp
 *
 *  Created on: May 15, 2013
 *      Author: mvis
 */

#pragma once

#include <string>
#include <stack>
#include <type_traits>

#include <boost/regex.hpp>

#include "../Defines.hpp"
#include "../Strategy/Settings.hpp"
#include "../Exceptions/notfounderror.hpp"
#include "../Packet/Packet.hpp"

using namespace std;

template<typename T, typename = void>
class CEnumToPair;

class CUtils {
public:
	template<typename Simple, typename Complex>
	static settingsType parseOptions(string str) {
		settingsType settings;

		for (uint32_t i = 0; i < Complex::getLastField(); i++) {
			string opt = CUtils::enumToPair<Complex>(i).second;
			string optName = CUtils::enumToPair<Complex>(i).first;
			try {
				pair<string, string> res = CUtils::getInternalOptions(str, opt);
				str = res.first;
				settingsType map = Complex().parseComplex(optName, res.second);
				if (!map.empty()) {
					settings.insert(map.begin(), map.end());
				}
			} catch (notfound_error &e) {
				//
			}
		}

		for (uint32_t i = 0; i < Simple::getLastField(); i++) {
			string opt = CUtils::enumToPair<Simple>(i).second;
			string optName = CUtils::enumToPair<Simple>(i).first;
			settings[optName] = false;
			boost::regex e(opt);
			boost::match_results<std::string::const_iterator> what;
			if (boost::regex_search(str, what, e)) {
				settings[optName] = true;
			}
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
	inline static pair<string, string> enumToPair(uint32_t enumValue) {
		return CEnumToPair<T>::process(enumValue);
	}

};

template<class T>
class CEnumToPair<T, typename enable_if<is_base_of<CBaseOption, T>::value>::type> {
public:
	static pair<string, string> process(uint32_t enumValue) {
		T obj;
		return obj.getFieldStr(enumValue);
	}
};

template<class T>
class CEnumToPair<T, typename enable_if<is_base_of<CPacket, T>::value>::type> {
public:
	static pair<string, string> process(uint32_t enumValue) {
		T obj(0, dataType());
		return obj.getFieldStr(enumValue);
	}

};

template<typename T>
inline string CUtils::enumToString(uint32_t enumValue) {
	return CUtils::enumToPair<T>(enumValue).first;
}

