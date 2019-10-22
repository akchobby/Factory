.PHONY= unparse_test

unparse_test:unparser.o sensors.o bme280.o
	gcc -Wall -o unparser unparser.o sensors.o bme280.o -DTEST -std=c99
unparser.o:unparser.c unparser.h sensors.h 
	gcc -Wall -c unparser.c -DTEST -std=c99
sensors.o:sensors.c bme280.h bme280_defs.h sensors.h
	gcc -Wall -c sensors.c -lwiringPi -lpthread -std=gnu99 
bme280.o: bme280.c bme280.h bme280_defs.h
	gcc -Wall -c bme280.c -std=gnu99
clean:
	rm -f unparser.o sensors.o bme280.o unparser
