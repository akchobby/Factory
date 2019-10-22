#include "common.h"
#include "client.h"

/*char *getServerIP() {
    return IP_MARC;
}*/

//TEST Functions
void *getDeviceID(void * arg){
    char *ID = "Device testing\0";
    while(1) {
		send_message(REV_1, POST, ID);
		send_message(REV_2, POST, ID);
		sleep(1);
	}
}

void *getDeviceIP(void *arg){
    char *IP = "192.168.47.XX\0";
    while(1) {
		send_message(REV_1, POST, IP);
		send_message(REV_2, POST, IP);
		sleep(1);
	}
}

//TEST
void command_handler(char *buffer) {
    //FILE *fp;
    //execute the call
    printf("Handler: %s\n", buffer);
    /*fp = popen(buffer, "r");
    if (fp != NULL) {
        //memset(buffer, 0, MAX);
        fgets(buffer, 6, fp);
    } else
        printf("ERROR\n");
    pclose(fp);*/
}

void make_packet(char *parsed_message, packet_t *packet, int type){
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
}
