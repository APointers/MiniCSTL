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

#ifndef __HASH_SET__
#define __HASH_SET__


 /**
 * Simple hash set implementation.
 *
 * The hash function of this implementation is only for integers and strings, 
 * and does not support other data structures such as floating-point numbers.
 *
 * Note: For integers and strings only.
 */
typedef void* hash_set_t;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	/**
	* init_hash_set: Allocate space, initialize (dynamic heap space).
	*/
	hash_set_t init_hash_set();

	/**
	* add_hset: Add 'value' to cset.
	* @value: element that need to be added.
	* @return 1 new hash is added, 0 is added to the existing hash.
	*/
	unsigned add_hset(hash_set_t cset, void* value);

	/**
	* put_hset: Add 'value' to the hash table 'cset', the actual implementation.
	* @hash: hash code.
	* @value: element that need to be added.
	* @return 1 new hash is added, 0 is added to the existing hash.
	*/
	unsigned put_hset(hash_set_t cset, long long hash, void* value);

	/**
	* contains_hset: Check whether 'value' is in the hash table 'cset'.
	* @value: value that needs to check.
	* @return 1 contain, 0 no contain.
	*/
	int contains_hset(hash_set_t cset, void* value);

	/**
	* contains_hash_hset: Check whether 'hash' is in the hash table 'cset'.
	* @hash: hash that needs to check.
	* @return 1 contain, 0 no contain.
	*/
	int contains_hash_hset(hash_set_t cset, long long hash);

	/**
	* delete_hset: Remove 'value' from the hash table.
	* @value: value that need to be deleted.
	*/
	void delete_hset(hash_set_t cset, void* value);

	/**
	* resize_hset: Reset the hash table.
	*/
	void resize_hset(hash_set_t cset);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif