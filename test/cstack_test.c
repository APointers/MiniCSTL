#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "test.h"


int stack_test()
{
	cstack* stk = NULL;
	int res = 0;

	create_cstack(stk, int, 10);
	printf("\n Push元素：\n");
	for (int i = 0; i < 100; i++)
	{
		push_cstack(stk, int, i * i * i);
		printf("%d\t", (int)(i * i * i));
	}
	printf("\n Pop元素：\n");
	int isempty = 0;
	empty_cstack(stk, &isempty);
	while (isempty != 1)
	{
		pop_cstack(stk, int, &res);
		printf("%d\t", res);
		empty_cstack(stk, &isempty);
	}

	return 0;
}