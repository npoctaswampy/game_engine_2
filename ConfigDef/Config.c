#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Config.h"
#include "../DataStructures/LinkedList.h"

void loadPlainText(config_p* config, char* fileName);
char* processKey(FILE* fp);
sdNode_p* getNextString(FILE* fp);
sdNode_p* processObject(FILE* fp);
sdNode_p* getNextInt(FILE* fp);
sdNode_p* getNextDict(FILE* fp);
char peekAtNextChar(FILE* fp);
char getNextDivider(FILE* fp);
void fastForwardTo(char val,FILE* fp);
sdNode_p* getNextArray(FILE* fp);
void destructConfDict(StringDict_p* dict);
void destructConfLinkedList(LinkedList_p* ll);


void initConfig(config_p* config){
	config->dict = NULL;
}

void destructConfig(config_p* config){
	destructConfDict(config->dict);
	free(config->dict);
	free(config);
}
	
void destructConfDict(StringDict_p* dict){
	LinkedList_p* keys = dict->keys;
	LinkedListNode_p* currentNode = getHeadLLNode(keys);
	sdNode_p* node = NULL;
	char* key = NULL;
	do{
		key = (char*) getDataFromLLNode(currentNode);
		node = retrieveFromDict(dict,key);
		if(strcmp(node->type,"Dict") == 0) destructConfDict(node->data);
		if(strcmp(node->type,"Array") == 0) destructConfLinkedList(node->data);
		free(node->data);
		free(node);
	}while((currentNode = getNextLLNode(currentNode)) != NULL);
	destructDict(dict);
}

void destructConfLinkedList(LinkedList_p* ll){
	LinkedListNode_p* currentNode = getHeadLLNode(ll);
	sdNode_p* node = NULL;
	do{
		node = getDataFromLLNode(currentNode);
		if(strcmp(node->type,"Dict") == 0) destructConfDict(node->data);
		if(strcmp(node->type,"Array") == 0) destructConfLinkedList(node->data);
		free(node->data);
		free(node);
	}while((currentNode = getNextLLNode(currentNode)) != NULL);
	destructLinkedList(ll);
}

void buildConfigFromFile(config_p* config, char* fileName, int binary){
	if(binary == 0) loadPlainText(config, fileName);
}

void loadPlainText(config_p* config, char* fileName){
    FILE* fp; 
    printf("Loading config...\n");
    
    if(access(fileName, F_OK) != -1){
        fp = fopen(fileName,"r");
        sdNode_p* dictNode = getNextDict(fp);
        config->dict = dictNode->data;
        free(dictNode); 
        fclose(fp);
    }
}	

char* processKey(FILE* fp){
	fastForwardTo('"',fp);
	sdNode_p* keyNode = getNextString(fp);

	char* key = keyNode->data;

	free(keyNode);
	return key;
}

sdNode_p* processObject(FILE* fp){
	void* val = NULL;	
	
	fastForwardTo(':',fp);
	char current = peekAtNextChar(fp);

	while(val == NULL) {
        if (current == '"') {
            current = fgetc(fp);
            val = (void *) getNextString(fp);
        }
        if (current >= '0' && current <= '9')
            val = getNextInt(fp);
        if (current == '{')
            val = getNextDict(fp);
        if (current == '[')
            val = getNextArray(fp);
        if(val == NULL){
            fgetc(fp);
            current = peekAtNextChar(fp);
        }
    }

	return val;
}

sdNode_p* getNextDict(FILE* fp){
    printf("Processing dict...\n");
    char* key;
    void* object;
    char current = peekAtNextChar(fp);	

    StringDict_p* dict = malloc(sizeof(StringDict_p));
    initDict(dict); 

    while(current != '}' && !feof(fp)){
            key = processKey(fp);
            object = processObject(fp);
            insertIntoDict(dict, key, object);
            current = getNextDivider(fp);
    }

    sdNode_p* node = (sdNode_p*) malloc(sizeof(sdNode_p));
    node->type = malloc(BUFFLEN*sizeof(char)); 
    strcpy(node->type,"Dict");
    node->data = dict;

    return node;
}

sdNode_p* getNextArray(FILE* fp){
	void* object;
	char current = peekAtNextChar(fp);

	LinkedList_p* list = malloc(sizeof(LinkedList_p));
	initLinkedList(list);

	while(current != ']' && !feof(fp)){
		object = getNextDict(fp);
		insertAtTail(list, object);
		current = getNextDivider(fp);
	}

	sdNode_p* node = malloc(sizeof(sdNode_p));
        node->type = malloc(BUFFLEN*sizeof(char)); 
        strcpy(node->type,"Array");
	node->data = list;

	return node;
}

sdNode_p* getNextString(FILE* fp){
    char* buffer = malloc(sizeof(char)*BUFFLEN);
    char current = fgetc(fp);

    int i = 0;
    do{
            buffer[i] = current;
            i++;
            current = fgetc(fp);
    }while(current != '"' && !feof(fp));

    buffer[i] = '\0';
    printf("Processing String %s\n",buffer);

    sdNode_p* node = malloc(sizeof(sdNode_p));
    node->type = malloc(BUFFLEN*sizeof(char)); 
    strcpy(node->type,"String");
    node->data = buffer;

    return node;
}

sdNode_p* getNextInt(FILE* fp){
    char* buffer = malloc(sizeof(char)*BUFFLEN);
    int* ret = malloc(sizeof(int));

    int i = 0;
    char current = fgetc(fp);

    do{
            buffer[i] = current;
            i++;
            current = fgetc(fp);
    }while(current != ',' && current != '}' && !feof(fp));
    ungetc(current, fp);

    buffer[i] = '\0';
    *ret = atoi(buffer);
    printf("Processing Int %d\n",*ret);

    free(buffer);

    sdNode_p* node = malloc(sizeof(sdNode_p));
    node->type = malloc(BUFFLEN*sizeof(char)); 
    strcpy(node->type,"Integer");
    node->data = ret;

    return node;
}

char peekAtNextChar(FILE* fp){
	char ret = fgetc(fp);	
	ungetc(ret, fp);
	return ret;
}

char getNextDivider(FILE* fp){
	char current = fgetc(fp);
	while(current != ',' && current != '}' && current !=']' && !feof(fp)){
		current = fgetc(fp);
	}
	return current;
}

void fastForwardTo(char val,FILE* fp){
	char current = fgetc(fp);
	while(current != val && !feof(fp))
		current = fgetc(fp);
}







