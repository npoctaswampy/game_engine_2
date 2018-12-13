#include <stdio.h>
#include <stdlib.h>
#include "StringDict.h"

int key_from_string(char* string);
void rehashIfNecessary(StringDict_p* dict);

void initDict(StringDict_p* dict){
	dict->table = table_construct(DICT_SIZE, LINEAR);
}

void destructDict(StringDict_p* dict){
	table_destruct(dict->table);
}

void insertIntoDict(StringDict_p* dict, char* key, void* value){
	int id = key_from_string(key);
	table_insert(dict->table, (hashkey_t) id, value);
	rehashIfNecessary(dict);
}

void* deleteFromDict(StringDict_p* dict, char* key){
	int id = key_from_string(key);
	return table_delete(dict->table, (hashkey_t) id);
}

void* retrieveFromDict(StringDict_p* dict, char* key){
	int id = key_from_string(key);
	return table_retrieve(dict->table, (hashkey_t) id);
}


void rehashIfNecessary(StringDict_p* dict){
	int threshold = dict->table->size / REHASH_DIV;
	if(dict->table->num_keys > threshold){
		printf("Rehashing...\n");
		int newTableSize = dict->table->size*REHASH_MULT;
		dict->table = table_rehash(dict->table, newTableSize);
	}
}


int key_from_string(char* string)
{
	int hash = 0;
	const int p = 31;
    	const int m = 1e9 + 9;
	int i = 0;
	int p_pow = 1;
	while(string[i] != '\0'){
		hash = (hash + (string[i] - 'a' + 1) * p_pow) % m;
		p_pow = (p_pow * p) % m;
		i++;
	}	
	return abs(hash);
}
