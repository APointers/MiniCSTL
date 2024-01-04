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

#ifndef __CARRAY_H__
#define __CARRAY_H__
#include <malloc.h>
#include <string.h>


 /**
 * Simple array implementation.
 *
 * The array of this implementation must be pre-empted with contiguous heap space,
 * and will not grow dynamically.
 *
 * Note:  The array does not grow dynamically.
 */
typedef struct carray_tag {
	void* _array;
	int _size;
}carray;


	/**
	* create_carray: Create an array of memory contiguous array, _this.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @size:  number of array elements.
	*/
#define	create_carray(_this,type,size) \
	do{ \
		int __size = (size);  \
		if((_this = (carray* )malloc(sizeof(carray))) && __size>0) { \
			if (__size>0 && (_this->_array = malloc(sizeof(type) * __size))) { \
					memset(_this->_array, 0, sizeof(type) * __size); \
					_this->_size = __size; \
			} \
		} \
	} while (0)

	/**
	* destroy_carray: Free up memory space _this array.
	* @_this: carray*  _this.
	*/
#define	destroy_carray(_this) \
	do{ \
		if(_this){ \
			if (_this->_array) free(_this->_array); \
			free(_this);  \
			(_this) = NULL; \
		} \
	} while (0)

	/**
	* copy_to_carray: Deepcopy array _this to des.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @des:   carray*  des, externally responsible for allocating/freeing memory.
	*/
#define	copy_to_carray(_this,type,des) \
	do{\
		if (_this && (des) && (des)->_size >= _this->_size){ \
			if (_this->_size && (des)->_array){ \
				memcpy((des)->_array, _this->_array,sizeof(type) * _this->_size); \
			} \
		} \
	} while (0)

	/**
	* remove_value_carray: Erase the value at the 'position' position.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @position:  the position of the removed element.
	*/
#define	remove_value_carray(_this,type,position) \
	do{ \
		int __pos = (position);  \
		if (_this && __pos >= 0 && __pos < _this->_size){ \
			type initElem; \
			memset(&initElem, 0, sizeof(type)); \
			*((type*)_this->_array + __pos) = initElem; \
		} \
	} while (0)

	/**
	* update_value_carray: Update the value at the 'position' to the 'value' value.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @position:  the position of the element to be updated.
	* @value:  the value that will use to update the 'position' element.
	*/
#define	update_value_carray(_this, type, position, value) \
	do{ \
		int __pos = (position);  \
		if (_this && __pos >= 0 && __pos < _this->_size){ \
			*((type*)_this->_array + __pos) = (value); \
		} \
	} while (0)

	/**
	* erase_carray: Erase all elements in the array _this.
	* @_this: carray*  _this.
	* @type:  array element type.
	*/
#define	erase_carray(_this,type) \
	do{ \
		if (!_this) break; \
		if(_this->_array && _this->_size){ \
			memset(_this->_array, 0, sizeof(type) * _this->_size); \
		} \
	} while (0)

	/**
	* switch_values_carray: Swap the elements at 'position1' and 'position2' in the array _this.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @position1:  
	* @position2:  
	*/
#define switch_values_carray(_this,type, position1, position2) \
	do{ \
		int __pos1 = (position1);  \
		int __pos2 = (position2);  \
		if(__pos1 == __pos2) break; \
		if (_this && __pos1 >= 0 && __pos1 < _this->_size && __pos2 >= 0 && __pos2 < _this->_size){ \
			type _temp = *((type*)_this->_array + __pos1); \
			*((type*)_this->_array + __pos1) = *((type*)_this->_array + __pos2); \
			*((type*)_this->_array + __pos2) = _temp; \
		} \
	} while (0)

	/**
	* reverse_carray: Invert Array (Element Position Inversion).
	* @_this: carray*  _this.
	* @type:  array element type.
	*/
#define reverse_carray(_this,type) \
	do{ \
		if (!_this) break; \
		int i; \
		for (i = 0; i < _this->_size / 2; i++){ \
			switch_values_carray(_this, type, i, _this->_size - i - 1); \
		} \
	} while (0)

	/**
	* bubble_sort_carray: bubble sort.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @TYPE_compare: the type of function pointer is  int (*)(void* elem1,void* elem2), 
	*				 0 elem1 == elem2; 1 elem1 > elem2; -1 elem1 < elem2.
	*/
#define bubble_sort_carray(_this,type,TYPE_compare) \
	do{ \
		if (!_this && !TYPE_compare) break; \
		int i, j; \
		for (i = 0; i < _this->_size - 1; i++){ \
			for (j = 0; j < _this->_size - i - 1; j++){ \
				if (TYPE_compare(((type*)_this->_array + j), ((type*)_this->_array + j + 1)) == 1){ \
					switch_values_carray(_this,type, j, j + 1); \
				} \
			} \
		} \
	} while (0)

	/**
	* selection_sort_carray: selection sort.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @TYPE_compare: the type of function pointer is  int (*)(void* elem1,void* elem2), 
	*				 0 elem1 == elem2; 1 elem1 > elem2; -1 elem1 < elem2.
	*/
#define selection_sort_carray(_this,type,TYPE_compare) \
	do{ \
		if (!_this && !TYPE_compare) break; \
		int i, j, min; \
		for (i = 0; i < _this->_size - 1; i++){ \
			min = i; \
			for (j = i + 1; j < _this->_size; j++) { \
				if (TYPE_compare(((type*)_this->_array + j), ((type*)_this->_array + min)) == -1) min = j; \
			} \
			switch_values_carray(_this, type, min, i); \
		} \
	} while (0)

	/**
	* insertion_sort_carray: insertion sort.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @TYPE_compare: the type of function pointer is  int (*)(void* elem1,void* elem2), 
	*				 0 elem1 == elem2; 1 elem1 > elem2; -1 elem1 < elem2.
	*/
#define insertion_sort_carray(_this,type,TYPE_compare) \
	do{ \
		if (!_this && !TYPE_compare) break; \
		int i, j; \
		type num; \
		for (i = 1; i < _this->_size; i++){ \
			num = *((type*)_this->_array +i); \
			j = i - 1; \
			while (j >= 0 && TYPE_compare(((type*)_this->_array +j),&num) == 1){ \
				*((type*)_this->_array + j + 1) = *((type*)_this->_array +j); \
				j--; \
			} \
			*((type*)_this->_array + j + 1) = num; \
		} \
	} while (0)

	/**
	* get_value_at_postion_carray: Get the value at the 'position' position.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @position:  
	* @pvalue: return the lookup value. Type*.
	*/
#define	get_value_at_postion_carray(_this,type,position,pvalue) \
	do{ \
		int __pos = (position);  \
		if (_this && __pos >= 0 && __pos < _this->_size){ \
			pvalue = *((type*)_this->_array + __pos); \
		} \
	} while (0)

	/**
	* count_of_value_carray: Find the number of 'value' in the array _this.
	* @_this: carray*  _this
	* @type:  array element type
	* @value: the lookup value
	* @pvalue: return the count of the lookup value,the type of 'pvalue' is int*.
	*/
#define count_of_value_carray(_this,type,value,pvalue) \
	do{ \
		int __value = (value);  \
		if (!_this && !pvalue) break; \
		int i, total = 0; \
		for (i = 0; i < _this->_size; i++){ \
			if (*((type*)_this->_array +i) == __value) total++; \
		} \
		*pvalue = total; \
	} while (0)

	/**
	* indexes_of_value_carray: Finds all indexes where the value is in the array _this.
	* @_this: carray*  _this.
	* @type:  array element type.
	* @value: the lookup value.
	* @result_array: an array that returns all indexes of the lookup value, with type carray*, 
	*				 element type int, and externally allocated memory.
	*/
#define indexes_of_value_carray(_this,type,value,result_array) \
	do { \
		int __value = (value);  \
		if (!_this && !result_array) break; \
		int total = 0; \
		count_of_value_carray(_this, type, __value, &total); \
		if (result_array->_size < total) break; \
		int i, j = 0; \
		for (i = 0; i < _this->_size; i++){ \
			if (*((type*)_this->_array +i) == __value){ \
				*((int*)result_array->_array + j) = i; \
				j++; \
			} \
		} \
	} while (0)

	/**
	* find_min_carray: Find the minimum value in the array _this
	* @_this: carray*  _this
	* @type:  array element type
	* @TYPE_compare: the type of function pointer is  int (*)(void* elem1,void* elem2), 
	*				 0 elem1 == elem2; 1 elem1 > elem2; -1 elem1 < elem2.
	* @pmin: return the lookup value,the type of 'pmin' is  int*.
	*/
#define find_min_carray(_this,type,TYPE_compare,pmin) \
	do{ \
		int i; \
		type min = *((type*)_this->_array); \
		for (i = 1; i < _this->_size; i++){ \
			if (TYPE_compare(((type*)_this->_array +i), &min) == -1){ \
				min = *((type*)_this->_array +i); \
			} \
		} \
		*(pmin) = min; \
	} while (0)

	/**
	* find_max_carray: Find the maximum value in the array _this
	* @_this: carray*  _this
	* @type:  array element type
	* @TYPE_compare: the type of function pointer is  int (*)(void* elem1,void* elem2), 
	*			     0 elem1 == elem2; 1 elem1 > elem2; -1 elem1 < elem2.
	* @pmax: return the lookup value,the type of pmax is int*.
	*/
#define find_max_carray(_this,type,TYPE_compare,pmax) \
	do{ \
		int i; \
		type max = *((type*)_this->_array); \
		for (i = 1; i < _this->_size; i++){ \
			if (TYPE_compare(((type*)_this->_array +i), &max) == 1){ \
				max = *((type*)_this->_array +i); \
			} \
		} \
		*(pmax) = max; \
	} while (0)

	/**
	* display_carray: Print the elements of the array _this sequentially.
	* @_this: carray*  _this
	* @type:  array element type
	*/
#define display_carray(_this,type) \
	do{ \
		int i; \
		for (i = 0; i < _this->_size; i++){ \
			printf("%d ", *((type*)_this->_array + i)); \
		} \
		printf("\n"); \
	} while (0)


#endif // !__CARRAY_H__