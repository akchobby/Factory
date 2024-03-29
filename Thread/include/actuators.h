#ifndef _actuators_h
#define _actuators_h

#include "sensors.h"

typedef struct actuator_data{
	char cmd[10];
	int led_nb;
	int led_state;
	int relay_state;
	char message[16];
	int alarm_;
	int id;
	char *actuator_list;
	
}actuator_data_t;

void changeLedState (actuator_data_t *);
void changeRelayState (actuator_data_t *);
void displayMessage (actuator_data_t *);
void getAlarm(actuator_data_t *);
void getActuatorList(actuator_data_t *);
void triggerAlarm(actuator_data_t *);
void *alarm_function();
void lcdDisplay_thread (sensor_data_t *);

#endif
