#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "parser.h"

#define BUFFER_SIZE_PS 256

typedef struct ParsedStorage ParsedStorage;

struct ParsedStorage {
	
	pthread_mutex_t parsedMutex;
	parsed_data_t *lastParsed;

};

void ParsedStorage_init(ParsedStorage *parsed) {
	
	//pck = (PacketStorage*) malloc(sizeof(struct PacketStorage));

	pthread_mutex_init(&(parsed->parsedMutex), NULL);

}

void ParsedStorage_read(ParsedStorage *parsed, parsed_data_t* buffer) {

	pthread_mutex_lock(&(parsed->parsedMutex));
	parsed->lastParsed = buffer;
	//strcpy(buffer, parsed->lastPacket);
	pthread_mutex_unlock(&(parsed->parsedMutex));

}

void ParsedStorage_write(ParsedStorage *parsed, parsed_data_t* buffer) {

	pthread_mutex_lock(&(parsed->parsedMutex));
	*buffer = parsed->lastParsed;
	//strcpy(parsed->lastPacket, buffer);
	pthread_mutex_unlock(&(parsed->parsedMutex));

}
