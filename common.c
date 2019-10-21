#include "common.h"

char *getServerIP() {
    return "127.0.0.1";
}

int getDeviceID(){
    return 0;
}

int getDeviceIP(){
    return 0;
}

//TEST
void command_handler(char *buffer) {
    FILE *fp;
    //execute the call
    printf("Handler: %s\n", buffer);
    fp = popen(buffer, "r");
    if (fp != NULL) {
        //memset(buffer, 0, MAX);
        fgets(buffer, 6, fp);
    } else
        printf("ERROR\n");
    pclose(fp);
}

void make_packet(char *parsed_message, packet_t *packet){
    packet->device_id = getDeviceID();
    packet->ip_address = getDeviceIP();
    memcpy(packet->message, parsed_message, sizeof(parsed_message));
}

void unmake_packet(char *parsed_message, packet_t *packet){
    packet->device_id = getDeviceID();
    packet->ip_address = getDeviceIP();
    memcpy(parsed_message, packet->message, sizeof(packet->message));
}
