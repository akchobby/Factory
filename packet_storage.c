#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "packet_storage.h"

#define BUFFER_SIZE_PS 256

/*
typedef struct PacketStorage PacketStorage;

struct PacketStorage {
	
	pthread_mutex_t packetMutex;
	char lastPacket[256];

};*/

PacketStorage PacketStorage_init() {
	
	PacketStorage pck;
	pck = (PacketStorage) malloc(sizeof(PacketStorage));
	
	//pck = (PacketStorage*) malloc(sizeof(struct PacketStorage));

	pthread_mutex_init(&(pck->packetMutex), NULL);
	
	return pck;

}

void PacketStorage_read(PacketStorage pck, char* buffer) {

	pthread_mutex_lock(&(pck->packetMutex));
	strcpy(buffer, (pck->lastPacket));
	pthread_mutex_unlock(&(pck->packetMutex));

}

void PacketStorage_write(PacketStorage pck, char* buffer) {

	pthread_mutex_lock(&(pck->packetMutex));
	strcpy((pck->lastPacket), buffer);
	pthread_mutex_unlock(&(pck->packetMutex));

}
