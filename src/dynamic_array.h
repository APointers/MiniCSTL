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

#ifndef __DYNAMIC_ARRAY__
#define __DYNAMIC_ARRAY__
#include <stdlib.h>
#include <string.h>


#define DEFAULT_CAPACITY 0x01 << 0x04
#define INDEX_OUT_OF_BOUNDS NULL

 /**
 * Simple dynamic array implementation.
 *
 * The dynamic array of this implementation mimics the vector of C++,
 * and supports dynamic growth.
 *
 * Note:  The dynamic array mimics the C++ vector, but the interface is different.
 */
typedef struct dynamic_array
{
	void* items;
	unsigned size;
	unsigned capacity;
} dynamic_array_t;


/**
* init_dynamic_array: Construct a dynamic array (dynamic heap space) _this receive the return value.
* @type: the real type of dynamic array element.
*/
#define init_dynamic_array(_this,type) \
    do{ \
        if (!(_this =(dynamic_array_t*)malloc(sizeof(dynamic_array_t)))) break; \
        _this->items = calloc(DEFAULT_CAPACITY, sizeof(type)); \
        _this->capacity = DEFAULT_CAPACITY; \
        _this->size = 0; \
    }while(0)

/**
* add_element_darray: Add a ‘pvalue’ to the _this at the end.
* @type: the real type of dynamic array element.
* @pvalue: type* , element that need to be added.
*/
#define add_element_darray(_this, type, pvalue) \
    do{ \
		if (_this->size >= _this->capacity){ \
			void *newItems = realloc(_this->items, (_this->capacity <<= 1) * sizeof(type)); \
			_this->items = newItems;  \
		} \
		memcpy(((type*)_this->items + _this->size),pvalue,sizeof(type)); \
		_this->size++; \
	} while (0)

/**
* put_element_darray: Put the 'pvalue' in the 'index' position.
* @type: the real type of dynamic array element.
* @pvalue: type* , element that need to be added.
* @index: int, the location where the element was added.
*/
#define put_element_darray(_this, type, pvalue, index) \
    do{ \
        if (_this->size < 0 || index >= _this->size) break;  \
        memcpy(((type*)_this->items + index),pvalue,sizeof(type)); \
    }while(0)

/**
* get_element_darray: Gets the element whose index is 'index'.
* @type: the real type of dynamic array element.
* @index: int, the 'index' position of the element to be fetched.
* @presult: type* , the return value obtained.
*/
#define get_element_darray(_this, type, index, presult) \
    do{ \
        if (_this->size < 0 || index >= _this->size) break;  \
        memcpy(presult, ((type*)_this->items + index), sizeof(type)); \
    } while (0)

/**
* delete_element_darray: Delete an element whose index is 'index'.
* @type: the real type of dynamic array element.
* @index: int, the index position of the element to be deleted.
*/
#define  delete_element_darray(_this, type, index) \
    do{ \
        if (_this->size < 0 || index >= _this->size)  break;  \
        for (unsigned i = index; i < _this->size; i++){ \
            *((type*)(_this->items)+i) = *((type*)(_this->items) + i + 1); \
        } \
        _this->size--; \
    } while (0)



#endif