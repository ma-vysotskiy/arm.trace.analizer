/*
 * enum_helper_pri.h
 *
 *  Created on: Apr 23, 2013
 *      Author: mvis
 */

#include "../Defines.hpp"
//before includeing this please define enumBody

//*
//- DEFINE WHAT WE ARE CONSTRUCTING NEXT (array of pair<string, string>)
//#define e_begin(arg) fieldStrPair arg##_s[SIZE]={
#define e_begin(arg) static const fieldStrPair& arg##_s(int i) { static const fieldStrPair a[] = {
#define e_member(arg,arg2) std::make_pair(#arg,#arg2) ,
//#define e_end  };
#define e_end };return a[i];}

enumBody

#undef e_begin
#undef e_member
#undef e_end
//*
//- UNDEFING
#undef delimiter
#undef last_enumerator
#undef member_value

