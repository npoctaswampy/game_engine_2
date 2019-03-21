#include "../DataStructures/StringDict.h"

#ifndef CONFIG
#define CONFIG

#define BUFFLEN 30

typedef enum{INT,STRING,ARRAY,DICT} dictTypes;

typedef struct Config_t{
	StringDict_p* dict; 
}config_p;

void initConfig(config_p* config);
void destructConfig(config_p* config);
void buildConfigFromFile(config_p* config, char* fileName, int binary);

#endif