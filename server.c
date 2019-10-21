#include <pthread.h>
#include "common.h"

//char buffer[MAX];
void *buffer;
// Function designed for chat between client and server. 
void *process_command(void *pthread_type) {
    pthread_arg_t *pthread_arg = (pthread_arg_t *) pthread_type;
    int socket_fd = pthread_arg->new_socket_fd;
    //struct sockaddr_in client_address = pthread_arg->client_address;
    char *message;

    packet_t *reply = malloc(sizeof(packet_t));
    read((socket_fd), buffer, sizeof(buffer));
    printf("Process command: %s\n", buffer);
    unmake_packet(message, (packet_t *) buffer);
    //process_message(message, reply);
    write(socket_fd, reply, sizeof(reply));

    command_handler(buffer); //temporal

    //SENT REPLY
    write((socket_fd), buffer, sizeof(buffer));
    //memset(buffer, 0, MAX);

    free(pthread_type);
    close(socket_fd);
    pthread_exit(0);
}

int start_server_listener(void) {
    pthread_arg_t th[MAX_THREADS];
    int main_sockfd, backSocket_connfd;
    socklen_t backSocket_len;
    struct sockaddr_in backSocket_servaddr, cli;
    pthread_attr_t pthread_attr;
    pthread_arg_t *pthread_arg;
    int opt = 1;
    int j = 1;

    // socket create and verification
    main_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (main_sockfd == -1) {
        printf("socket creation failed...\n");
        return ERROR_NO_FACTORY;
    } else
        printf("Socket successfully created..\n");

    bzero(&backSocket_servaddr, sizeof(backSocket_servaddr));

    if (setsockopt(main_sockfd, SOL_SOCKET, SO_REUSEADDR /*| SO_REUSEPORT*/, (char *) (&opt), sizeof(opt)) < 0)
        return ERROR_NO_FACTORY;

    // assign IP, PORT
    backSocket_servaddr.sin_family = AF_INET;
    backSocket_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    backSocket_servaddr.sin_addr.s_addr = inet_addr(getServerIP());
    backSocket_servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(main_sockfd, (SA *) &backSocket_servaddr, sizeof(backSocket_servaddr))) != 0) {
        printf("socket bind failed...\n");
        return ERROR_NO_FACTORY;
    } else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(main_sockfd, MAX_THREADS)) != 0) {
        return ERROR_NO_FACTORY;
    }
    //else
    //	printf("Server listening..\n");


    /* Initialise pthread attribute to create detached threads. */
    if (pthread_attr_init(&pthread_attr) != 0) {
        printf("pthread_attr_init");
        return ERROR_NO_FACTORY;
    }
    if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        printf("pthread_attr_setdetachstate");
        return ERROR_NO_FACTORY;
    }

    for (;;) {
        pthread_arg = (pthread_arg_t *) malloc(sizeof *pthread_arg);
        backSocket_len = sizeof(pthread_arg->client_address);
        // Accept the data packet from client and verification
        backSocket_connfd = accept(main_sockfd, (SA *) &pthread_arg->client_address, &backSocket_len);
        if (backSocket_connfd < 0) {
            printf("server acccept failed...\n");
            free(pthread_arg);
            return ERROR_NO_FACTORY;
        }
        //else
        //	printf("server acccept the client...\n");
        pthread_arg->new_socket_fd = backSocket_connfd;

        // Function for between client and server
        pthread_arg->pid = 0;
        pthread_arg->isAlive = 1;
        if (pthread_create(&pthread_arg->pid, &pthread_attr, process_command, (void *) &pthread_arg) != 0) {
            printf("Server background thread error: %d\n", ERROR_NO_FACTORY);
            free(pthread_arg);
        } else
            printf("Server thread %d @ %s created\n", j++, getServerIP());

        /*if(j > MAX_THREADS){
            for(j = 0; j < MAX_THREADS; j++){
                pthread_join(th[j].pid, NULL);
                printf("Server thread %d finished\n", j);
            }
        }*/
        //check thread liveness
        for (int k = 0; k < j; k++) {
            if (th[k].isAlive != 1)
                pthread_join(th[k].pid, NULL);
        }
        // Close the socket
        //close(main_sockfd);
    }
    printf("END\n");
    return 0;
} 

