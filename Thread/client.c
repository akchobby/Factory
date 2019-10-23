#include "common.h"

int _send_message(char *ip_address, int type, char* message) {
    int client_socket;
    struct sockaddr_in servaddr;
	char *pack_to_dashboard;
	
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
        packet_t packet;
        
        printf("Packing... \n");
		//packet.device_id = 1;
		packet.message_type = type;
        
        if(packet.message_type == DASHBOARD){
			pack_to_dashboard = malloc(128);
			//snprintf(pack_to_dashboard, 4, "%d", packet.device_id);
			//strcat(pack_to_dashboard, ";");
			strcat(pack_to_dashboard, packet.org_ip_address);
			strcat(pack_to_dashboard, ";");
			strcat(pack_to_dashboard, message);
			 //send packet 2 dashboard
			//printf("Send packet 2 dashboard %ld\n", sizeof(pack_to_dashboard));
			printf("Message: %s\n", pack_to_dashboard);
			if(write(client_socket, &pack_to_dashboard, sizeof(pack_to_dashboard)) < 0)
				printf("CLIENT: Error message to Dashboard\n");
			free(pack_to_dashboard);
	} else {
		strcpy(packet.send_ip_address, ip_address);
		strcpy(packet.org_ip_address, device.ip_address);//, strlen(ip)+1);
		strcpy(packet.message, message);//, strlen(parsed_message));
		
		//send packet
		printf("Send packet %d\n", sizeof(packet));
		if(write(client_socket, &packet, sizeof(packet_t)) < 0)
			return ERROR_NO_FACTORY;
	}
    }

    // close the socket
    close(client_socket);
    return 0;
}

int send_message(int type, PacketStorage message) {
    int client_socket;
    struct sockaddr_in servaddr;
	char *pack_to_dashboard;
	packet_t packet;
	int i = 0;
	
    //printf("CLIENT: Searching factory @ %s...\n", ip_address);

    // socket create and verify
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("CLIENT: socket creation failed...\n");
        return ERROR_NO_FACTORY;
    } else {
	printf("CLIENT: Socket successfully created..\n");
    }
	pack_to_dashboard = malloc(256);
	if(type == FACTORY){
		for(; i < 6; i++){
			if(list_devices[i].isConnected == 0)
				continue;
			bzero(&servaddr, sizeof(servaddr));
			// assign IP, PORT
			servaddr.sin_family = AF_INET;
			servaddr.sin_addr.s_addr = inet_addr(list_devices[i].ip_address);
			servaddr.sin_port = htons(PORT);		

			// try to connect
			if (connect(client_socket, (SA *) &servaddr, sizeof(servaddr)) != 0) {
				printf("CLIENT: connection with the server failed...\n");
				usleep(100);
			} else 
				printf("CLIENT: Client connected to server %s\n", list_devices[i].ip_address);
				
				
			strcat(pack_to_dashboard, list_devices[i].ip_address);
			strcat(pack_to_dashboard, ";");
			strcat(pack_to_dashboard, packet.org_ip_address);
			strcat(pack_to_dashboard, ";");
			PacketStorage_read(message, pack_to_dashboard);
					
			//send packet
			printf("Send packet %d\n", sizeof(packet));
			if(write(client_socket, pack_to_dashboard, sizeof(pack_to_dashboard)) < 0)
				return ERROR_NO_FACTORY;
		}
		free(pack_to_dashboard);
	} 
	if((type & DASHBOARD) == DASHBOARD){
		strcat(pack_to_dashboard, dashboard_device.ip_address);
		strcat(pack_to_dashboard, ";");
		strcat(pack_to_dashboard, packet.org_ip_address);
		strcat(pack_to_dashboard, ";");
		PacketStorage_read(message, pack_to_dashboard);
		
		//printf("Send packet 2 dashboard %ld\n", sizeof(pack_to_dashboard));
		printf("Message: %s\n", pack_to_dashboard);
		if(write(client_socket, &pack_to_dashboard, sizeof(pack_to_dashboard)) < 0)
			printf("CLIENT: Error message to Dashboard\n");
		free(pack_to_dashboard);
	}

    // close the socket
    close(client_socket);
    return 0;
}


/*void *client_listener(void *args){
	int client_socket;
    struct sockaddr_in servaddr;
	//char packet[256];
	char *pack_to_dashboard;
	device_t packet;
    //printf("CLIENT: Searching factory @ %s...\n", ip_address);

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
    servaddr.sin_port = htons(PORT);
	while(1) {
		if(PacketStorage_read(output_pck, &packet) == 0))
			packet.message_type = DASHBOARD | FACTORY;
		else if(PacketStorage_read(periodic_pck, &packet) == 0))
			packet.message_type = DASHBOARD | FACTORY;

			
	    servaddr.sin_addr.s_addr = inet_addr(packet.ip_address);
	    // try to connect
		if (connect(client_socket, (SA *) &servaddr, sizeof(servaddr)) != 0) {
			printf("CLIENT: connection with the server failed...\n");
			usleep(100);
		}
		
		if(packet.message_type == DASHBOARD){
			pack_to_dashboard = malloc(128);
			//snprintf(pack_to_dashboard, 4, "%d", packet.device_id);
			//strcat(pack_to_dashboard, ";");
			strcat(pack_to_dashboard, packet.org_ip_address);
			strcat(pack_to_dashboard, ";");
			strcat(pack_to_dashboard, message);
			 //send packet 2 dashboard
			//printf("Send packet 2 dashboard %ld\n", sizeof(pack_to_dashboard));
			printf("Message: %s\n", pack_to_dashboard);
			if(write(client_socket, &pack_to_dashboard, sizeof(pack_to_dashboard)) < 0)
				printf("CLIENT: Error message to Dashboard\n");
			free(pack_to_dashboard);
		} else {
			strcpy(packet.send_ip_address, ip_address);
			strcpy(packet.org_ip_address, device.ip_address);//, strlen(ip)+1);
			strcpy(packet.message, message);//, strlen(parsed_message));
			
			//send packet
			printf("Send packet %ld\n", sizeof(packet));
			if(write(client_socket, &packet, sizeof(packet_t)) < 0)
				return ERROR_NO_FACTORY;
		}
	}
}*/
