
#options: ANT/MARC/None

all: 
	gcc -Wall -o comm server.c common.c client.c main.c -I. -lpthread -DANT
	
clean:
	rm comm
	

