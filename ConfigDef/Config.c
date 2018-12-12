#include <stdio.h>
#include <stdlib.h>
#include "Config.h"

void loadPlainText(Config_p* config, char* fileName);
char* processKey(FILE* fp);
char* getNextString(FILE* fp);
void* processObject(FILE* fp);
int* getNextInt(FILE* fp, int current);


void initConfig(Config_p* config){
	config->dict = malloc(sizeof(StringDict_p));
	initDict(config->dict); 
}

void destructFileReader(Config_p* config){
	destructDict(config->dict);
}

void buildConfigFromFile(Config_p* config, char* fileName, int binary){
	if(binary == 0) loadPlainText(config, fileName);
}

void loadPlainText(Config_p* config, char* fileName){
	FILE* fp = fopen(fileName,"r");
	char* key;
	void* object;

	while(!feof(fp)){
		key = processKey(fp);
		object = processObject(fp);
		insertIntoDict(config->dict, key, object);
	}
	
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

	current = fgetc(fp);

	if(current == '"')
		val = (void*) getNextString(fp);
	if(current >= '0' && current <= '9')
		val = (void*) getNextInt(fp, current);

	return val;
}

char* getNextString(FILE* fp){
	char* buffer = malloc(sizeof(char)*BUFFLEN);
	char current = fgetc(fp);
	
	int i = 0;
	while(current != '"' && !feof(fp)){
		buffer[i] = current;
		i++;
		current = fgetc(fp);
	};

	buffer[i] = '\0';

	return buffer;
}

int* getNextInt(FILE* fp, int current){
	char* buffer = malloc(sizeof(char)*BUFFLEN);
	int* ret = malloc(sizeof(int));	

	int i = 0;
	while(current != ',' && !feof(fp)){
		buffer[i] = current;
		i++;
		current = fgetc(fp);
	};

	buffer[i] = '\0';
	*ret = atoi(buffer);

	return ret;
}












