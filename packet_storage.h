#ifndef PACKET_STORAGE_H
#define PACKET_STORAGE_H

typedef struct PacketStorage PacketStorage;

void PacketStorage_init(PacketStorage *pck);
void PacketStorage_read(PacketStorage *pck, char* buffer);
void PacketStorage_write(PacketStorage *pck, char* buffer);

#endif
