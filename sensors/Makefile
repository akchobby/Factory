.PHONY= sensor_thread

sensor_thread:sensors.o bme280.o
	gcc -Wall -o sensor_thread sensors.o bme280.o -lwiringPi -lpthread -std=gnu99
test:sensors_test bme280.o
	gcc -Wall -o sensor_thread sensors.o bme280.o -lwiringPi -lpthread -std=gnu99 
sensors.o:sensors.c bme280.h bme280_defs.h sensors.h
	gcc -Wall -c sensors.c -lwiringPi -lpthread -std=gnu99 
sensors_test: sensors.c bme280.h bme280_defs.h sensors.h
	gcc -Wall -c sensors.c -DTEST -lwiringPi -lpthread -std=gnu99 
bme280.o: bme280.c bme280.h bme280_defs.h
	gcc -Wall -c bme280.c -std=gnu99
clean:
	rm sensors.o bme280.o sensor_thread
