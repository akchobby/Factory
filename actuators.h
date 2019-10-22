#ifndef _actuators_h
#define _actuators_h

typedef struct actuator_data{
	char cmd[10];
	int led_nb;
	int led_state;
	int relay_state;
	char message[16];
	int alarm;
}actuator_data_t;

void changeLedState (parsed_data_t *);
void changeRelayState (parsed_data_t *);
void displayMessage (parsed_data_t *);
void getAlarm(parsed_data_t *);
void triggerAlarm(parsed_data_t *);
void *alarm(void *);
void *lcdDisplay_thread (void *);

#endif
