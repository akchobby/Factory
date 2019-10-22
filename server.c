#include "common.h"

// Function designed for chat between client and server. 
void *process_command(void *pthread_type) {
    thread_t *pthread_arg = pthread_type;
    int socket_fd = pthread_arg->new_socket_fd;

    //struct sockaddr_in client_address = pthread_arg->client_address;
    char *message; //TODO: test
    packet_t *buffer = malloc(sizeof(packet_t));
	//printf("Process command... %d\n", sizeof(packet_t));

    //receive
    if(read(socket_fd, buffer, sizeof(packet_t)) < 0)
		printf("Process command error... \n");
    //printf("Process command: %s\n", buffer);
    
    //unpack
    //unmake_packet(message, (packet_t *) buffer);
    printf("Unpacking message... \n");
	message = malloc(strlen(buffer->message));
    memcpy(message, buffer->message, strlen(buffer->message));
    //printf("Command... %s\n", message);
    //process
    //printf("%s\n", message);
    //command_handler(message); 
    packet_handler(buffer);
    
    //printf("Command Processed... %s\n", message);

	free(buffer);
	free(message);
    close(socket_fd);
    pthread_arg->isAlive = 0;
    pthread_exit(0);
}

void *start_server_listener(void *args) {
    //thread_t th[MAX_THREADS];
    int main_sockfd, backSocket_connfd;
    socklen_t backSocket_len;
    struct sockaddr_in backSocket_servaddr;
    pthread_attr_t pthread_attr;
    thread_t thread_arg;
    int opt = 1;
    int j = 1;

    // socket create and verification
    main_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (main_sockfd == -1) {
        printf("SERVER: socket creation failed...\n");
        //return ERROR_NO_FACTORY;
    } else
        printf("SERVER: Socket successfully created..\n");

    bzero(&backSocket_servaddr, sizeof(backSocket_servaddr));

    if (setsockopt(main_sockfd, SOL_SOCKET, SO_REUSEADDR /*| SO_REUSEPORT*/, (char *) (&opt), sizeof(opt)) < 0)
		printf("SERVER: Socket options error..\n");
        //return ERROR_NO_FACTORY;

    // assign IP, PORT
    backSocket_servaddr.sin_family = AF_INET;
    backSocket_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    backSocket_servaddr.sin_addr.s_addr = inet_addr(device.ip_address);
    backSocket_servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(main_sockfd, (SA *) &backSocket_servaddr, sizeof(backSocket_servaddr))) != 0) {
        printf("SERVER: socket bind failed...\n");
        //return ERROR_NO_FACTORY;
    } else {
		printf("SERVER: Socket successfully binded..\n");
	}
	device.isConnected = 1;
    // Now server is ready to listen and verification
    if ((listen(main_sockfd, MAX_THREADS)) != 0) {
		printf("SERVER: Socket unsuccessfully..\n");
        //return ERROR_NO_FACTORY;
    }
    //else
    //	printf("Server listening..\n");


    /* Initialise pthread attribute to create detached threads. */
    if (pthread_attr_init(&pthread_attr) != 0) {
        printf("SERVER: pthread_attr_init");
        //return ERROR_NO_FACTORY;
    }
    if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        printf("SERVER: pthread_attr_setdetachstate");
        //return ERROR_NO_FACTORY;
    }

    for (;;) {
        //thread_arg = (thread_t *) malloc(sizeof (thread_t));
        backSocket_len = sizeof(thread_arg.client_address);
        // Accept the datathread_arg packet from client and verification
        backSocket_connfd = accept(main_sockfd, (SA *) &thread_arg.client_address, &backSocket_len);
        if (backSocket_connfd < 0) {
            printf("SERVER: server acccept failed...\n");
            //free(thread_arg);
            //return ERROR_NO_FACTORY;
        }
        //else
        //printf("SERVER: server acccept the client... scokfd: %d \n",thread_arg.new_socket_fd);
        thread_arg.new_socket_fd = backSocket_connfd;

        // Function for between client and server
        thread_arg.pid = 0;
        thread_arg.isAlive = 1;
        if (pthread_create(&thread_arg.pid, &pthread_attr, process_command, (void *) &thread_arg) != 0) {
            printf("SERVER: Server background thread error: %d\n", ERROR_NO_FACTORY);
            //free(thread_arg);
        } else
            printf("SERVER: Server thread %d @ %s created\n", j, device.ip_address);

        /*if(j > MAX_THREADS){
            for(j = 0; j < MAX_THREADS; j++){
                pthread_join(th[j].pid, NULL);
                printf("Server thread %d finished\n", j);
            }
        }*/
        //check thread liveness
        /*for (int k = 0; k < j; k++) {
            if (th[k].isAlive != 1)
                pthread_join(th[k].pid, NULL);
        }*/
        // Close the socket
        //close(main_sockfd);
    }
    printf("SERVER: END\n");
    return 0;
} 

