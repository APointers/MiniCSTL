#include "cdict.h"
#include <stdio.h>
#include <stdlib.h>


#define MAXELEMENTS 1000

/**
* special data type called '__cdictionary'
* for generic use
*/
typedef struct cdictionary_tag
{
	/* void* array for generic use of the __cdictionary.there actual saves the entries. */
	void* elements[MAXELEMENTS];

	/* contains the number of elements in this __cdictionary */
	int number_of_elements;

} __cdictionary;


/*
* utility function
* sdbm hash algorithm
* @returns a hashcode for the given string 's'
*/
int get_hash(char s[]);


/* simple constructor */
cdict create_dict()
{
	__cdictionary* p_dict = (__cdictionary*)malloc(sizeof(__cdictionary));
	if (p_dict)
	{
		p_dict->number_of_elements = 0;

		/* initializes the elemens of the array with NULL-pointer */
		for (int i = 0; i < MAXELEMENTS; i++)
		{
			p_dict->elements[i] = NULL;
		}

		return p_dict;
	}
	else
	{
		printf("unable to create a __cdictionary\n");
		return NULL;
	}
}


int add_item_label(cdict dict, char label[], void* item)
{
	unsigned int index = get_hash(label);

	/* make sure index is fitting */
	if (index < MAXELEMENTS)
	{
		((__cdictionary*)dict)->elements[index] = item;
		return 0;
	}

	/* error case */
	return -1;
}

int add_item_index(cdict dict, int index, void* item)
{
	__cdictionary* __dict = (__cdictionary*)dict;
	if (!__dict->elements[index])
	{
		__dict->elements[index] = item;
		return 0;
	}
	return -1;
}

void* get_element_label(cdict dict, char s[])
{
	__cdictionary* __dict = (__cdictionary*)dict;
	int index = get_hash(s);
	if (__dict->elements[index])
	{
		return __dict->elements[index];
	}

	printf("None entry at given label\n");
	return NULL;
}

void* get_element_index(cdict dict, int index)
{
	__cdictionary* __dict = (__cdictionary*)dict;
	if (index >= 0 && index < MAXELEMENTS)
	{
		return __dict->elements[index];
	}

	printf("index out of bounds!\n");
	return NULL;
}

void destroy(cdict dict)
{
	free(dict);
}


int get_hash(char s[])
{
	unsigned int hash_code = 0;

	/* iterates over string at each character */
	for (int counter = 0; s[counter] != '\0'; counter++)
	{
		/* actual computing of the hash code */
		hash_code =
			s[counter] + (hash_code << 6) + (hash_code << 16) - hash_code;
	}

	/* % modulo is for fitting the index in array. */
	return hash_code % MAXELEMENTS;
}