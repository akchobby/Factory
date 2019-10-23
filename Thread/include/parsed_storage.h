#ifndef PARSED_STORAGE_H
#define PARSED_STORAGE_H

#include "parser.h"

typedef struct s_ParsedStorage {
	
	pthread_mutex_t parsedMutex;
	parsed_data_t *lastParsed;
	
} *ParsedStorage;

ParsedStorage ParsedStorage_init();
void ParsedStorage_read(ParsedStorage parsed, parsed_data_t *buffer);
void ParsedStorage_write(ParsedStorage parsed, parsed_data_t *buffer);

#endif
