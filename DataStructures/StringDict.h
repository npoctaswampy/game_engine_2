#include "../Common.h"

#ifndef STRINGDICT
#define STRINGDICT

#include "LinkedList.h"

#define REHASH_DIV 2
#define REHASH_MULT 3
#define DICT_SIZE 10


typedef struct StringDict_t {
	table_t* table;
	LinkedList_p* keys;
} StringDict_p;

typedef struct sdNode_t{
	char* type;
	void* data;
} sdNode_p;

void initDict(StringDict_p* dict);
void destructDict(StringDict_p* dict);
void insertIntoDict(StringDict_p* dict, char* key, sdNode_p* value);
sdNode_p* deleteFromDict(StringDict_p* dict, char* key);
sdNode_p* retrieveFromDict(StringDict_p* dict, char* key);

#endif