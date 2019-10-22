#include "common.h"

int send_message(char *ip_address, int type, char* message) {
    int client_socket;
    struct sockaddr_in servaddr;
    //char buff[MAX];

    printf("CLIENT: Searching factory @ %s...\n", ip_address);

    // socket create and verify
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("CLIENT: socket creation failed...\n");
        return ERROR_NO_FACTORY;
    } else
        printf("CLIENT: Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip_address);
    servaddr.sin_port = htons(PORT);

    // try to connect
    if (connect(client_socket, (SA *) &servaddr, sizeof(servaddr)) != 0) {
        printf("CLIENT: connection with the server failed...\n");
        usleep(100);
        //close(sock);
        //return ERROR_NO_FACTORY;
    } else {
        printf("CLIENT: Client connected to server %s\n", ip_address);
        
        //TEST
        packet_t packet;

        printf("Packing... \n");
		packet.device_id = 1;
		packet.message_type = type;
		strcpy(packet.ip_address, SERV);//, strlen(ip)+1);
		strcpy(packet.message, message);//, strlen(parsed_message));
        //make_packet(message, &packet, type);
        
        //send packet
        //printf("Send packet %d\n", sizeof(packet));
        if(write(client_socket, &packet, sizeof(packet_t)) < 0)
			return ERROR_NO_FACTORY;
     
        
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
