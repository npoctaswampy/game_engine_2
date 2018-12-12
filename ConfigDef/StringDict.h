#include "table.h"

#ifndef STRINGDICT
#define STRINGDICT

#define DICT_SIZE 100

typedef struct StringDict_t {
	table_t* table;
} StringDict_p;

void initDict(StringDict_p* dict);
void destructDict(StringDict_p* dict);
void insertIntoDict(StringDict_p* dict, char* key, void* value);
void* deleteFromDict(StringDict_p* dict, char* key);
void* retrieveFromDict(StringDict_p* dict, char* key);

#endif
