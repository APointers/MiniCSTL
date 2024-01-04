#include <stdio.h>
#include <stdlib.h>
#include "hash_set.h"


#define DEFAULT_HASH_SET_CAPACITY 1 << 10

typedef struct
{
	unsigned capacity;
	unsigned length;
	void** values;
	void** keys;
} __hash_set_t;

long long __hash(void* value);
unsigned __retrieve_index_from_hash(const long long __hash, const unsigned capacity);

hash_set_t init_hash_set()
{
	__hash_set_t* set = NULL;
	if (!(set = (__hash_set_t*)malloc(sizeof(__hash_set_t)))) return NULL;
	set->keys = calloc(DEFAULT_HASH_SET_CAPACITY, sizeof(void**));
	set->values = calloc(DEFAULT_HASH_SET_CAPACITY, sizeof(void**));
	set->length = 0;
	set->capacity = DEFAULT_HASH_SET_CAPACITY;

	return set;
}

unsigned add_hset(hash_set_t cset, void* value)
{
	__hash_set_t* set = (__hash_set_t*)cset;
	return put_hset(set, __hash(value), value);
}

unsigned put_hset(hash_set_t cset, long long __hash, void* value)
{
	__hash_set_t* set = (__hash_set_t*)cset;
	if (contains_hash_hset(set, __hash))
	{
		if (set->keys[__retrieve_index_from_hash(__hash, set->capacity)] == value) return 0;
		// collision
		resize_hset(set);
		return put_hset(set, __hash, value);
	}
	set->keys[__retrieve_index_from_hash(__hash, set->capacity)] = value;
	set->values[set->length++] = value;
	return 1;
}

int contains_hset(hash_set_t cset, void* value)
{
	__hash_set_t* set = (__hash_set_t*)cset;
	return set->keys[__retrieve_index_from_hash(__hash(value), set->capacity)] == value ? 1 : 0;
}

int contains_hash_hset(hash_set_t cset, long long __hash)
{
	__hash_set_t* set = (__hash_set_t*)cset;
	return set->keys[__retrieve_index_from_hash(__hash, set->capacity)] ? 1 : 0;
}

void delete_hset(hash_set_t cset, void* value)
{
	__hash_set_t* set = (__hash_set_t*)cset;
	set->keys[__retrieve_index_from_hash(__hash(value), set->capacity)] = NULL;
}

void resize_hset(hash_set_t cset)
{
	__hash_set_t* set = (__hash_set_t*)cset;
	void** keys_resized = calloc((set->capacity <<= 1), sizeof(void**));
	for (int i = 0; i < set->length; i++)
	{
		keys_resized[__retrieve_index_from_hash(__hash(set->values[i]), set->capacity)] = set->values[i];
	}
	free(set->keys);
	set->keys = keys_resized;
	void** new_values = (void**)realloc(set->values, set->capacity * sizeof(void**));
	set->values = new_values;
}


// adler_32 __hash
long long __hash(void* value)
{
	char* str = (char*)value;
	int a = 1;
	int b = 0;
	const int MODADLER = 65521;
	for (int i = 0; str[i] != '\0'; i++)
	{
		a = (a + str[i]) % MODADLER;
		b = (b + a) % MODADLER;
	}
	return (b << 16) | a;
}

unsigned __retrieve_index_from_hash(const long long __hash, const unsigned capacity)
{
	return (capacity - 1) & (__hash ^ (__hash >> 12));
}