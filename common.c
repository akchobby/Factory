#include "common.h"
#include "client.h"
#include "server.h"

/*char *getServerIP() {
    return IP_MARC;
}*/

//TEST Functions
void *getDeviceID(void * arg){
    char *ID = "Device testing\0";
    while(1) {
		send_message(REV_1, POST, ID);
		//send_message(REV_2, POST, ID);
		sleep(1);
	}
}

void *getDeviceIP(void *arg){
    char *IP = "192.168.47.XX\0";
    while(1) {
		send_message(REV_1, POST, IP);
		//send_message(REV_2, POST, IP);
		sleep(1);
	}
}

void _getDeviceIP(char *command, char *ip){
    FILE *fd;
    fd = popen(command, "r");
    if (fd != NULL) {
        fgets(ip, 14, fd);
    } else
        printf("ERROR\n");
    pclose(fd);
}

void init_communications(void) {
	pthread_t server = 0;
	pthread_attr_t attr;
	
	//get the own ip
	char *ip = malloc(14);
    _getDeviceIP("ifconfig | grep \"inet 192.\" | awk '{print $2}'", ip);
	strcpy(device.ip_address, ip);
	printf("IP: %s\n", device.ip_address);
	
	//start server	
	/* Initialise pthread attribute to create detached threads. */
    if (pthread_attr_init(&attr) != 0) {
        printf("SERVER: pthread_attr_init");
        //return ERROR_NO_FACTORY;
    }
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
        printf("SERVER: pthread_attr_setdetachstate");
        //return ERROR_NO_FACTORY;
    }
    
    pthread_create(&server, &attr, start_server_listener, NULL);
    usleep(100);

	//look for all possible boards in the network
	for(int i = 25; i < 50; i++){
		snprintf(ip, 14, "192.168.47.%d", i);
		if(strcmp(ip, device.ip_address) != 0){
			send_message(ip, GET, "ifconfig | grep \"inet 192.\" | awk '{print $2}'");
			send_message(ip, DASHBOARD, "echo $DASHBOARD");
		}
	}
	
	for(int i = 0; i < 7; i++){
		if(list_devices[i].isConnected){
			ip = list_devices[i].ip_address;
			send_message(ip, POST, device.ip_address);
		}	
	}
	free(ip);
	//find the dashboard ip
}

//TEST
void command_handler(char *buffer) {
    FILE *fp;
    //execute the call
    printf("Handler: %s\n", buffer);
    fp = popen(buffer, "r");
    if (fp != NULL) {
        fgets(buffer, strlen(buffer), fp);
    } else
        printf("ERROR\n");
    pclose(fp);
}

void packet_handler(packet_t *buffer) {
	FILE *fp;
	char *ret = malloc(strlen(buffer->message));
	if(buffer->message_type == GET){
		//execute the call
		printf("Packet_handler: %s\n", buffer->message);
		fp = popen(buffer->message, "r");
		if (fp != NULL) {
			fgets(ret, strlen(buffer->message), fp);
		} else
			printf("ERROR\n");
		pclose(fp);
		if(ret != NULL)
			send_message(buffer->org_ip_address, POST, ret);
	} else {
		printf("%s\n", buffer->message);
		return;
	}
    free(ret);
    
    
}

/*void make_packet(char *parsed_message, packet_t *packet, int type){
	printf("Packing... \n");
    packet->device_id = 1;
    packet->message_type = type;
    char *ip = SERV;
   // char *test;
   // memcpy(test, "TEST", strlen("TEST"));
    //printf("TEST %s\n", test);
    printf("1. Copy %s len %d\n", ip, strlen(ip));
    //packet->ip_address = malloc(strlen(ip)+1);
    strcpy(packet->ip_address, ip);//, strlen(ip)+1);
    printf("Copied %s len %d\n", packet->ip_address, strlen(ip));
    //packet->message = malloc(strlen(parsed_message));
    strcpy(packet->message, parsed_message);//, strlen(parsed_message));
    printf("Sending %s len %d\n", parsed_message, strlen(parsed_message));
}

void unmake_packet(char *parsed_message, packet_t *packet){
	printf("Unpacking message... \n");
	parsed_message = malloc(strlen(packet->message));
    memcpy(parsed_message, packet->message, strlen(packet->message));
    printf("Message... %s\n", parsed_message);
}*/
