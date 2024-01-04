#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int dynamic_array_test()
{
	dynamic_array_t* da = NULL;
	init_dynamic_array(da, int);

	for (int i = 0; i < 20; i++)
	{
		add_element_darray(da, int, &i);
	}
	printf("20 elements\n");
	for (int i = 0; i < da->size; i++)
	{
		int temp = 0;
		get_element_darray(da, int, i, &temp);
		printf("%d\t", temp);
	}

	delete_element_darray(da, int, 10);

	printf("\n\n19 elements,delete index 10 element:\n");
	for (int i = 0; i < da->size; i++)
	{
		int temp = 0;
		get_element_darray(da, int, i, &temp);
		printf("%d\t", temp);
	}


	int value = 1000;

	put_element_darray(da, int, &value, 0);

	printf("\n\n19 elements,update index 0 element to 1000:\n");
	for (int i = 0; i < da->size; i++)
	{
		int temp = 0;
		get_element_darray(da, int, i, &temp);
		printf("%d\t", temp);
	}
	value = 5000;
	int another_value = 7000;
	add_element_darray(da, int, &another_value);

	printf("\n\n20 elements, add index 19 element to 7000:\n");
	for (int i = 0; i < da->size; i++)
	{
		int temp = 0;
		get_element_darray(da, int, i, &temp);
		printf("%d\t", temp);
	}

	int value_for_invalid_index = 10000;
	put_element_darray(da, int, &value_for_invalid_index, 150);

	printf("\n\nupdate a invalid index 150 element to 10000:\n");
	for (int i = 0; i < da->size; i++)
	{
		int temp = 0;
		get_element_darray(da, int, i, &temp);
		printf("%d\t", temp);
	}

	return 0;
}