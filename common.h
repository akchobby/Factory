#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 8080
#define SA struct sockaddr
#define MAX_THREADS 8

#define MAX 80
#define ERROR_NO_FACTORY -1
#define GET
#define POST

typedef struct {
    int new_socket_fd;
    struct sockaddr_in client_address;
    pthread_t pid;
    int isAlive;
} pthread_arg_t;

typedef struct {
    int device_id;
    char *ip_address;
    char *message;
} packet_t;

char *getServerIP();
void command_handler(char *buffer);
void make_packet(char *message, packet_t *package);
void unmake_packet(char *message, packet_t *package);