CC = gcc
CFLAGS = -std=gnu99 -Wall -pedantic -fsanitize=address
S = src
B = bin
I = include
ADDLIB = -lpthread -lwiringPi -static-libasan

.PHONY: compile

.DEFAULT_GOAL: compile

compile:
	@echo "Starting compilation..."
	$(CC) $(CFLAGS) -I$(I) $(S)/*.c -o $(B)/main $(ADDLIB)
	@echo "Compilation complete!"
