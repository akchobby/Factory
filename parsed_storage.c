#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "parser.h"
#include "parsed_storage.h"

#define BUFFER_SIZE_PS 256

/*typedef struct ParsedStorage ParsedStorage;

struct ParsedStorage {
	
	pthread_mutex_t parsedMutex;
	parsed_data_t *lastParsed;

};*/

ParsedStorage ParsedStorage_init() {
	
	ParsedStorage parsed;
	//printf("test\n");
	parsed = (ParsedStorage) malloc(sizeof(struct s_ParsedStorage));
	//pck = (PacketStorage*) malloc(sizeof(struct PacketStorage));
	//printf("test2\n");
	pthread_mutex_init(&(parsed->parsedMutex), NULL);
	
	return parsed;

}

void ParsedStorage_read(ParsedStorage parsed, parsed_data_t *buffer) {

	pthread_mutex_lock(&(parsed->parsedMutex));
	buffer = parsed->lastParsed;
	//strcpy(buffer, parsed->lastPacket);
	pthread_mutex_unlock(&(parsed->parsedMutex));

}

void ParsedStorage_write(ParsedStorage parsed, parsed_data_t *buffer) {

	pthread_mutex_lock(&(parsed->parsedMutex));
	parsed->lastParsed = buffer;
	//strcpy(parsed->lastPacket, buffer);
	pthread_mutex_unlock(&(parsed->parsedMutex));

}
