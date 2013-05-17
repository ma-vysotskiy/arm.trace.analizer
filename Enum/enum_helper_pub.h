/*
 * color.h
 *
 *  Created on: Apr 19, 2013
 *      Author: mvis
 */



	GETLASTFIELD

//before includeing this please define enumBody

//*
//- DEFINE WHAT WE ARE CONSTRUCTING (enum)
#define e_begin(arg) enum arg {
#define e_member(arg,arg2) arg ,
#define e_end  SIZE};

enumBody

#undef e_begin
#undef e_member
#undef e_end

//*
//- UNDEFING
#undef delimiter
#undef last_enumerator
#undef member_value

