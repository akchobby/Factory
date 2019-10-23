#ifndef PACKET_STORAGE_H
#define PACKET_STORAGE_H

typedef struct s_PacketStorage {
	
	pthread_mutex_t packetMutex;
	char lastPacket[256];

} *PacketStorage;

PacketStorage PacketStorage_init();
void PacketStorage_read(PacketStorage pck, char* buffer);
void PacketStorage_write(PacketStorage pck, char* buffer);

#endif
