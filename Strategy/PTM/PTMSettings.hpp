/*
 * PTMSettings.hpp
 *
 *  Created on: May 8, 2013
 *      Author: mvis
 */

#pragma once

#include <string>
#include <functional>
#include <algorithm>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include "../../Defines.hpp"
#include "../../Strategy/StrategySettings.hpp"
#include "../../Strategy/Settings.hpp"
#include "../../Common/Utils.hpp"
#include "../../Exceptions/notfounderror.hpp"
#include "../../Packet/PTM/PTMPackets.hpp"

using namespace std;

class CPTMSimpleOption;
class CPTMComplexOption;

class CPTMSettings : public CStrategySettings {
public:
	void init(string str) {
		settings = CUtils::parseOptions<CPTMSimpleOption, CPTMComplexOption>(
				str);
	}
};

#define STATICFIELDGETTER
#undef enumBody
#define enumBody \
e_begin(field) \
	e_member(CycleCount, %cc) \
	e_member(ContextID, %ci) \
e_end

class CPTMSimpleOption : public CBaseOption {
public:
#include "../../Enum/enum_helper_pub.h"
//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"
};

#undef enumBody
#define enumBody \
e_begin(field) \
	e_member(Output, output) \
	e_member(Id, id) \
e_end

class equal_pair : public binary_function<settingsType::value_type,
		settingsType::value_type::second_type, bool> {
public:
	bool operator()(settingsType::value_type x,
			settingsType::value_type::second_type y) const {
		return x.second == y;
	}
};

template<typename T>
class deleteter : public unary_function<T*, void> {
public:
	void operator ()(T* obj) {
		delete obj;
	}
};
class f {
public:
	void operator()(settingsType::value_type x) {
		cout << x.first << "|" << x.second << endl;
	}
};

class CPTMComplexOption : public CBaseComplexOption {
public:
	CPTMComplexOption() :
			packets { new CPTMAsyncPacket(0, dataType()), new CPTMAtomPacket(1,
					dataType()), new CPTMBranchPacket(2, dataType()),
					new CPTMContextIDPacket(3, dataType()),
					new CPTMExceptionReturnPacket(4, dataType()),
					new CPTMIgnorePacket(5, dataType()), new CPTMIsyncPacket(6,
							dataType()), new CPTMTimestampPacket(7, dataType()),
					new CPTMTriggerPacket(8, dataType()),
					new CPTMWaypointPacket(9, dataType()) } {
	}
	~CPTMComplexOption() {
		for_each(packets.begin(), packets.end(), deleteter<CPacket>());
	}
	settingsType parseComplex(string opt, string toParse) {
		settingsType settings;
		using namespace std::placeholders;
		// if we need to parse output options
		if (opt
				== CUtils::enumToString<CPTMComplexOption>(
						CPTMComplexOption::Output)) {
			//parse them
			settings = parseOutput(toParse);
			// find if parseOutput did not enable any option
			settingsType::iterator it = find_if(settings.begin(),
					settings.end(), bind(equal_pair(), _1, 1));

			// yes, all opts disabled - reverse to default
			if (it == settings.end()) {
				//default all output opts are enabled
				settings = fillMap(1,
						CUtils::enumToString<CPTMComplexOption>(
								CPTMComplexOption::Output));
			}
		} else if (opt
				== CUtils::enumToString<CPTMComplexOption>(
						CPTMComplexOption::Id)) {
			try {
				uint32_t id = boost::lexical_cast<int>(toParse);
				settings[opt] = id;
			} catch (boost::bad_lexical_cast const&) {
				std::cout << "Error: input string was not valid" << std::endl;
			}
		}

		return settings;
		//parse string and flag present opts as enabled, other opts as disabled
	}
#include "../../Enum/enum_helper_pub.h"
//strings asociated with enum
#include "../../Enum/enum_helper_pri.h"
private:
	settingsType fillMap(uint32_t value, string optPrefix) {
		settingsType output;
		// if we have some prefix like output add separator '_'
		if (optPrefix != "") {
			optPrefix = optPrefix + "_";
		}
		// scan
		for (uint32_t i = 0; i < packets.size(); ++i) {
			CPacket* packet = packets[i];
			for (uint32_t j = 0; j < packet->getLastField(); ++j) {
				string opt(optPrefix + packet->getFieldStr(j).first);
				output[opt] = value;
			}
		}
		return output;
	}

	settingsType parseOutput(string toParse) {
		settingsType output;
		// set all opts as disabled
		string prefix = CUtils::enumToString<CPTMComplexOption>(
				CPTMComplexOption::Output);
		output = fillMap(0, prefix);
		// now check input and enable requested options
		for (vector<CPacket*>::iterator it = packets.begin();
				it != packets.end(); it++) {
			// scan all fields
			for (uint32_t enumVal = 0; enumVal < (*it)->getLastField();
					enumVal++) {
				// option's short name
				string opt = (*it)->getFieldStr(enumVal).second;
				// opttion's full name
				string optName = (*it)->getFieldStr(enumVal).first;
				// form regular expression
				//todo: why "\\b"+opt+"\\b" do not work as i espect?
				boost::regex e(opt);
				boost::match_results<std::string::const_iterator> what;
				// if found then enable options
				if (boost::regex_search(toParse, what, e)) {
					output[prefix + "_" + optName] = true;
				}
			}
		}
		return output;
	}

	vector<CPacket*> packets;
};

#undef STATICFIELDGETTER
