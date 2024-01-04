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

#ifndef __CSTACK_H__
#define __CSTACK_H__
#include <malloc.h>
#include <string.h>



 /**
 * Simple stack implementation.
 *
 * The stack of this implementation must be pre-empted with contiguous heap space,
 * and will not grow dynamically.
 *
 * Note:  The stack does not grow dynamically.
 */
typedef struct cstack_tag {
	void* _stack;
	int _top;
	int _max_size;
}cstack;


/**
* create_cstack: Create a stack space with memory contiguity.
* @_this: cstack*  _this.
* @type:  the type of stack element.
* @size:  the number of pre-developed stack elements.
*/
#define	create_cstack(_this,type,size) \
	do{ \
		int __size = (size);  \
		if((_this = (cstack* )malloc(sizeof(cstack))) && (__size)>0) { \
			if ((__size)>0 && (_this->_stack = malloc(sizeof(type) * __size))) { \
					memset(_this->_stack, 0, sizeof(type) * __size); \
					_this->_top = -1; \
					_this->_max_size = __size; \
			} \
		} \
	} while (0)

/**
* destroy_cstack: Free stack memory space.
* @_this: cstack*  _this.
*/
#define	destroy_cstack(_this) \
	do{ \
		if(_this){ \
			if (_this->_stack) free(_this->_stack); \
			free(_this); \
			_this = NULL; \
		} \
	} while (0)

/**
* pop_cstack: Pop the top element of the stack.
* @_this: cstack*  _this.
* @type:  the type of stack element.
* @pvalue: type*, the value of the pop-up element.
*/
#define	pop_cstack(_this,type,pvalue) \
	do{ \
		int* __pvalue = (pvalue); \
		if (_this && _this->_top >= 0)*__pvalue = *((type*)_this->_stack + _this->_top); \
		_this->_top--; \
	} while (0)

/**
* push_cstack: Push the 'value' value to the top of the stack.
* @_this: cstack*  _this.
* @type:  the type of stack element.
* @value:  the type of 'value' is 'type'.
*/
#define	push_cstack(_this, type, value) \
	do{ \
		if (_this && _this->_top < _this->_max_size){ \
			_this->_top++; \
			*((type*)_this->_stack + _this->_top) = (value); \
		} \
	} while (0)

/**
* empty_cstack: Check whether the stack is empty.
* @_this: cstack*  _this.
* @presult: the type of 'presult' is int*, 1 when the stack is empty, otherwise it is 0.
*/
#define empty_cstack(_this, presult) \
	do{ \
		int* __presult = (presult);  \
		if (!_this) break; \
		if (_this->_top == -1) *__presult = 1; \
		else *__presult = 0; \
	} while (0)

/**
* peek_cstack: The top element of the stack is returned, and the top element of the stack does not pop up.
* @_this: cstack*  _this.
* @type:  the type of stack element.
* @presult:  the type of 'presult' is type*, the value of the element at the top of the stack.
*/
#define peek_cstack(_this,type,presult) \
	do{ \
		int* __presult = (presult);  \
		if (!_this) break; \
		if (_this->_top >= 0) *__presult = *((type*)_this->_stack + _this->_top); \
	} while (0)


#endif // !__CSTACK_H__