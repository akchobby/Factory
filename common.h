#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

#ifdef MARC
	#define SERV "192.168.47.47"
	#define REV_1 "192.168.47.28"
	#define REV_2 "192.168.47.40"
#elif ANT
	#define SERV "192.168.47.38"
	#define REV_1 "192.168.47.47"
	#define REV_2 "192.168.47.40"
#else
	#define SERV "192.168.47.40"
	#define REV_1 "192.168.47.38"
	#define REV_2 "192.168.47.47"
#endif

#define PORT 8080
#define SA struct sockaddr
#define MAX_THREADS 8

#define MAX 80
#define ERROR_NO_FACTORY -1
#define GET 1
#define POST 2
#define DASHBOARD 3

typedef struct {
    int new_socket_fd;
    struct sockaddr_in client_address;
    pthread_t pid;
    int isAlive;
} thread_t;

typedef struct __attribute__((packed)) {
    int device_id;
    char org_ip_address[32];
    char send_ip_address[32];
    char message[64];
    int message_type;
} packet_t;

typedef struct {
	char ip_address[14];
	int isConnected;
} device_t;

device_t list_devices[7];
device_t device;

char *getServerIP();
void _getDeviceIP(char *command, char *ip);
void *getDeviceIP(void *args);
void *getDeviceID(void * arg);
void init_communications(void);
void command_handler(char *buffer);
void packet_handler(packet_t *buffer);
void make_packet(char *message, packet_t *package, int type);
void unmake_packet(char *message, packet_t *package);
