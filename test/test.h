#ifndef __TEST_H__
#define __TEST_H__
#include "carray.h"
#include "ckernel_list.h"
#include "cstack.h"
#include "cdict.h"
#include "dynamic_array.h"
#include "hash_set.h"


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

void test_sort();
void test_API();

int dynamic_array_test();

int ckernel_list_test();

int cdict_test();

int hash_set_test();

int stack_test();


#ifdef __cplusplus
}
#endif // __cplusplus


#endif