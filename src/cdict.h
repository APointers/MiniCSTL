/**
 * Copyright (C) 2024 sma.  All rights reserved.
 *
 * This header was taken from the sma
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.
 */

#ifndef __CDICT_H__
#define __CDICT_H__


 /**
 * Simple dictionary implementation.
 *
 * The hash function of this implementation is only for integers and strings,
 * and does not support other data structures such as floating-point numbers.
 *
 * Note:  The cdict prepares space for 1000 elements.
 */
typedef void* cdict;


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	/**
	* create_dict: is a simple constructor for creating
	* 			a cdict and setting up the
	* 			member field 'number_of_elements'
	* 			and prepares the inner array 'elements'
	*/
	cdict create_dict();

	/**
	* add_item_label: adds item (void*) to the cdict at given label
	* @label: key used to get hash code
	* @item: value reference to the key
	* @returns 0 if adding was sucessful otherwise -1
	*
	*/
	int add_item_label(cdict dict, char label[], void* item);

	/**
	* add_item_index: adds item (void*) to the cdict at given index (int)
	* @index:  key,equal to the hash was born by get_hash()
	* @item: value reference to the key
	* @returns 0 if adding was sucessful otherwise -1
	*/
	int add_item_index(cdict dict, int index, void* item);

	/**
	* get_element: returns the element at given label
	* @s: key
	* @return value reference to the key
	*/
	void* get_element_label(cdict dict, char s[]);

	/**
	* get_element: returns the element at given index
	* @index: key,equal to the hash was born by get_hash()
	* @return value reference to the key
	*/
	void* get_element_index(cdict dict, int index);

	/**
	* destroy: simple destrcutor function
	*/
	void destroy(cdict dict);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif  //!__CDICT_H__