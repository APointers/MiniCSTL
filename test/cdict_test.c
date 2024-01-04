#include <stdio.h>
#include "test.h"


int cdict_test()
{
	cdict testObj1;
	cdict testObj2;

	int value = 28;
	int value1 = 29;

	testObj1 = create_dict();
	testObj2 = create_dict();

	add_item_label(testObj1, "age", &value);
	add_item_label(testObj1, "age", &value1);
	add_item_label(testObj2, "name", "Christian");

	/*
		test for function add_item_label

		attention:
		The void* pointer must be convert into an int* pointer.
		After that you can dereference it.
	*/
	printf("My age is %d\n", *((int*)get_element_label(testObj1, "age")));
	printf("My name is %s\n", (char*)get_element_label(testObj2, "name"));

	/* test for function add_item_index */
	if (!add_item_index(testObj1, 0, &value))
	{
		printf("My age at index %d is %d\n", 0,
			*((int*)get_element_index(testObj1, 0)));
	}

	/* error scenario */
	/* get_element_label(testObj,"none"); */

	/* tidy up */
	destroy(testObj1);
	destroy(testObj2);

	return 0;
}