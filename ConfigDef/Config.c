#include <stdio.h>
#include <stdlib.h>
#include "Config.h"

void loadPlainText(Config_p* config, char* fileName);
char* processKey(FILE* fp);
char* getNextString(FILE* fp);
void* processObject(FILE* fp);
int* getNextInt(FILE* fp);
StringDict_p* getNextDict(FILE* fp);
char peekAtNextChar(FILE* fp);
char getNextDivider(FILE* fp);


void initConfig(Config_p* config){
	config->dict = NULL;
}

void destructFileReader(Config_p* config){
	destructDict(config->dict);
}

void buildConfigFromFile(Config_p* config, char* fileName, int binary){
	if(binary == 0) loadPlainText(config, fileName);
}

void loadPlainText(Config_p* config, char* fileName){
	FILE* fp = fopen(fileName,"r");

	config->dict = getNextDict(fp); 
	
	fclose(fp);
}	

char* processKey(FILE* fp){
	char current = fgetc(fp);

	while(current != '"' && !feof(fp)) 
		current = fgetc(fp);

	char* key = getNextString(fp);
	return key;
}

void* processObject(FILE* fp){
	char current = fgetc(fp);
	void* val = NULL;	
	
	while(current != ':' && !feof(fp))
		current = fgetc(fp);

	current = peekAtNextChar(fp);

	if(current == '"'){
		current = fgetc(fp);	
		val = (void*) getNextString(fp);
	}

	if(current >= '0' && current <= '9')
		val = (void*) getNextInt(fp);
	if(current == '{')
		val = (void*) getNextDict(fp);

	return val;
}

StringDict_p* getNextDict(FILE* fp){
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

	return dict;
}

char* getNextString(FILE* fp){
	char* buffer = malloc(sizeof(char)*BUFFLEN);
	char current = fgetc(fp);
	
	int i = 0;
	do{
		buffer[i] = current;
		i++;
		current = fgetc(fp);
	}while(current != '"' && !feof(fp));

	buffer[i] = '\0';

	return buffer;
}

int* getNextInt(FILE* fp){
	char* buffer = malloc(sizeof(char)*BUFFLEN);
	int* ret = malloc(sizeof(int));

	int i = 0;
	char current = fgetc(fp);

	while(peekAtNextChar(fp) != ',' && peekAtNextChar(fp) != '}' && !feof(fp)){
		buffer[i] = current;
		i++;
		current = fgetc(fp);
	};

	buffer[i] = '\0';
	*ret = atoi(buffer);

	return ret;
}

char peekAtNextChar(FILE* fp){
	char ret = fgetc(fp);	
	ungetc(ret, fp);
	return ret;
}

char getNextDivider(FILE* fp){
	char current = fgetc(fp);
	while(current != ',' && current != '}' && !feof(fp)){
		current = fgetc(fp);
	}
	return current;
}








