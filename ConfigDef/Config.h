#include "StringDict.h"

#ifndef CONFIG
#define CONFIG

#define BUFFLEN 30

typedef enum{NONE,KEY,VALUE} valType;

typedef struct Config_t{
	StringDict_p* dict; 
}Config_p;

void initConfig(Config_p* config);
void destructFileReader(Config_p* config);
void buildConfigFromFile(Config_p* config, char* fileName, int binary);

#endif
