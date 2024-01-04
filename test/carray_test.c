#include <stdio.h>
#include <time.h>
#include "test.h"

int comp(void* e1, void* e2)
{
	if (*(int*)e1 > *(int*)e2) return 1;
	else if (*(int*)e1 == *(int*)e2)  return 0;
	else  return -1;
}

void test_sort()
{
	printf("\n");
	printf(" +-------------------------------------+\n");
	printf(" |                                     |\n");
	printf(" |               C Array               |\n");
	printf(" |                                     |\n");
	printf(" +-------------------------------------+\n");
	printf("\n");

	carray* temp = NULL;
	create_carray(temp, int, 1000);

	int i;
	for (i = 0; i < temp->_size; i++)
	{
		update_value_carray(temp, int, i, temp->_size - i);
	}

	printf("Entered array is:\n");
	display_carray(temp, int);

	carray* c_array = NULL;
	create_carray(c_array, int, 1000);
	copy_to_carray(temp, int, c_array);
	carray* darray = NULL;
	create_carray(darray, int, 1000);
	copy_to_carray(temp, int, darray);

	printf("\nBubble Sort:");
	clock_t begin1 = clock();
	// Timing bubble sort
	bubble_sort_carray(temp, int, comp);
	clock_t end1 = clock();
	double time_spent1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
	display_carray(temp, int);

	printf("\nSelection Sort:");
	clock_t begin2 = clock();
	// Timing selection sort
	selection_sort_carray(c_array, int, comp);
	clock_t end2 = clock();
	double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
	display_carray(c_array, int);

	printf("\nInsertion Sort:");
	clock_t begin3 = clock();
	// Timing insertion sort
	insertion_sort_carray(darray, int, comp);
	clock_t end3 = clock();
	double time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
	display_carray(c_array, int);

	printf("\nTotal time spent for bubble sort: %lf seconds", time_spent1);
	printf("\nTotal time spent for selection sort: %lf seconds", time_spent2);
	printf("\nTotal time spent for insertion sort: %lf seconds", time_spent3);

	destroy_carray(temp);
	destroy_carray(c_array);
	destroy_carray(darray);
}

void test_API()
{
	printf("\n");
	printf(" +-------------------------------------+\n");
	printf(" |                                     |\n");
	printf(" |               C Array               |\n");
	printf(" |                                     |\n");
	printf(" +-------------------------------------+\n");
	printf("\n");

	carray* temp = NULL;
	create_carray(temp, int, 1000);

	int i;
	for (i = 0; i < temp->_size; i++)
	{
		update_value_carray(temp, int, i, i + 1);
	}
	for (i = temp->_size / 2; i < temp->_size; i++)
	{
		update_value_carray(temp, int, i, temp->_size - i);
	}

	printf("Entered array is:\n");
	display_carray(temp, int);

	//for (i = 0; i < temp->_size; i++)
	//{
	//	remove_value_carray(temp, int, i);
	//}
	//printf("remove_value_carray array is:\n");
	//display_carray(temp, int);

	//// Erase
	//for (i = 0; i < temp->_size; i++)
	//{
	//	update_value_carray(temp,int, i, i + 5);
	//}
	//printf("update_value_carray array is:\n");
	//display_carray(temp, int);  // Should give all 0s
	//
	//erase_carray(temp,int);
	//printf("erase_carray array is:\n");
	//display_carray(temp, int);  // Should give all 0s
	//for (i = 0; i < temp->_size / 2; i++)
	//{
	//	switch_values_carray(temp,int, i, temp->_size - i - 1);
	//}
	//printf("switch_values_carray array is:\n");
	//display_carray(temp, int);
	//reverse_carray(temp, int);
	//printf("reverse_carray array is:\n");
	//display_carray(temp, int);
	// 
	//int res = 0;
	//count_of_value_carray(temp, int, 50, &res);
	//printf("CountOf 50 in carray*  is:%d\n", res);

	//carray*  resultArr = NULL;
	//create_carray(resultArr, int, 10);
	//indexes_of_value_carray(temp, int, 50, resultArr);
	//display_carray(resultArr, int);
	int pmin = 0;
	find_min_carray(temp, int, comp, &pmin);
	printf("find_min_carray in carray temp is:%d\n", pmin);
	int pmax = 0;
	find_max_carray(temp, int, comp, &pmax);
	printf("find_max_carray in carray temp is:%d\n", pmax);

	destroy_carray(temp);
}


