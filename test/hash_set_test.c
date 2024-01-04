#include <stdio.h>

#include "test.h"

int hash_set_test()
{
	hash_set_t set = init_hash_set();

	char* v1 = "10.0", * v2 = "20.0", * v3 = "30.0", * v4 = "40.0", * v5 = "50.0", * v6 = "60.0", * v7 = "70.0";

	printf("Value %s was add_hset ? %d\n", v1, add_hset(set, &v1));
	printf("Value %s was add_hset ? %d\n", v1, add_hset(set, &v1));
	printf("contains_hset %s ? %d\n", v1, contains_hset(set, &v1));

	printf("Value %s was add_hset ? %d\n", v2, add_hset(set, &v2));
	printf("Value %s was add_hset ? %d\n", v2, add_hset(set, &v2));
	printf("contains_hset %s ? %d\n", v2, contains_hset(set, &v2));

	printf("Value %s was add_hset ? %d\n", v3, add_hset(set, &v3));
	printf("Value %s is add_hset ? %d\n", v3, add_hset(set, &v3));
	printf("contains_hset %s ? %d\n", v3, contains_hset(set, &v3));

	printf("Value %s was add_hset ? %d\n", v4, add_hset(set, &v4));
	printf("Value %s was add_hset ? %d\n", v4, add_hset(set, &v4));
	printf("contains_hset %s ? %d\n", v4, contains_hset(set, &v4));

	printf("Value %s was add_hset ? %d\n", v5, add_hset(set, &v5));
	printf("Value %s was add_hset ? %d\n", v5, add_hset(set, &v5));
	printf("contains_hset %s ? %d\n", v5, contains_hset(set, &v5));

	printf("Value %s is add_hset ? %d\n", v6, add_hset(set, &v6));
	printf("Value %s is add_hset ? %d\n", v6, add_hset(set, &v6));
	printf("contains_hset %s ? %d\n", v6, contains_hset(set, &v6));

	printf("contains_hset %s ? %d\n", v7, contains_hset(set, &v7));

	delete_hset(set, &v6);

	printf("contains_hset %s ? %d\n", v6, contains_hset(set, &v6));

	return 0;
}