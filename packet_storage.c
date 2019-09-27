#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct PacketStorage PacketStorage;

struct PacketStorage {
	
	pthread_mutex_t packetMutex;
	char* lastPacket[200];

};

PacketStorage PacketStorage_init() {

	PacketStorage pck;	
	
	pthread_mutex_init(&(pck->packetMutex), NULL);
	
	return pck;

}

void PacketStorage_read(PacketStorage pck, char* buffer) {

	pthread_mutex_lock(&(pck->packetMutex));
	memcpy((void *) buffer, (void *) pck->lastPacket, 200);
	pthread_mutex_unlock(&(pck->packetMutex));

}
