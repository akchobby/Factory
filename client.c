#include "common.h"

int send_message(char *ip_address, int type, char* message) {
    int client_socket;
    struct sockaddr_in servaddr;
    char buff[MAX];

    printf("Searching factory @ %s...\n", ip_address);

    // socket create and verify
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("socket creation failed...\n");
        return ERROR_NO_FACTORY;
    } else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip_address);
    servaddr.sin_port = htons(PORT);

    // try to connect
    if (connect(client_socket, (SA *) &servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        usleep(100);
        //close(sock);
        //return ERROR_NO_FACTORY;
    } else {
        printf("Client connected to server %s\n", ip_address);
        //TEST
        packet_t *packet = malloc(sizeof(packet_t));
        make_packet(message, packet);
        write(client_socket, &packet, sizeof(packet));
        read(client_socket, buff, strlen(buff));
        unmake_packet(buff, packet);
        free(packet);
        /*while (1) {
            //memset(buff, 0, MAX);
            strncpy(buff, "echo $DEVICE_ID", MAX);
            printf("%ld\n", strlen(buff));
            printf("Sending command: '%s'\n", buff);
            write(client_socket, buff, strlen(buff));
            //memset(buff, 0, strlen(buff));
            //printf("%s\n", buff);
            read(client_socket, buff, 6);
            //printf("%s\n", buff);
            printf("Device: %s located at IP %s\n", buff, ip_address);
            sleep(1);
        }*/
    }

    // close the socket
    close(client_socket);
    return 0;
}
