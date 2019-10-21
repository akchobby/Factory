
all: 
	gcc -Wall -o factory server.c common.c client.c main.c -I. -lpthread
	
server:
	gcc -Wall -o server server.c common.c main.c -I. -lpthread
	
client:
	gcc -Wall -o client client.c common.c main_client.c -I. -lpthread
	
clean:
	rm server client
	

