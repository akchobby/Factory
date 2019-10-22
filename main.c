#include "server.h"
#include "client.h"
#include "common.h"

/*int main(void) {
    start_server_listener();
    return 0;
}*/

int main(void) {
	pthread_t server = 0, th1 = 0, th2 = 0;
	//pthread_create(&server, NULL, start_server_listener, NULL);
	//usleep(10);
	init_communications();
	//pthread_create(&th1, NULL, getDeviceIP, NULL);
	//pthread_create(&th2, NULL, getDeviceID, NULL);
	
	//pthread_join(th1, NULL);
	//pthread_join(th2, NULL);
	//pthread_join(server, NULL);
	for(;;) {}
	return 0;
}
