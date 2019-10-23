#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include "i2clcd.h"
#include "GPIO.h"
#include "parser.h"
#include "actuators.h"

// Define some device parameters
#define I2C_ADDR   0x27 // I2C device address

int alarm_ = 0;

void changeLedState (actuator_data_t *ledState);
void changeRelayState (actuator_data_t *relayState);
void displayMessage (actuator_data_t *lcdState);
void triggerAlarm(actuator_data_t *alarmState);
void *alarm_function();
void *lcdDisplay_thread (void *arg);


#ifdef TEST
int main(int argc ,char **argv){
	   
	return 0;
}
#endif

void changeLedState (actuator_data_t *ledState) {
	int GPIO_nb = 0;
	if(ledState->led_nb == 0){
		GPIO_nb = 19;
	} else {
		GPIO_nb = 26;
	}
	
	if(ledState->led_state == 1){
		GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
		set_GPIO_state(resp, GPIO_nb, true);
		free(resp);
	} else if (ledState->led_state == 0) {
		GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
		set_GPIO_state(resp, GPIO_nb, false);
		free(resp);
	} else {
		printf("Error while trying to change LED state.\n");
	}
	strcpy(ledState->cmd, "A_LED");
}

void changeRelayState (actuator_data_t *relayState) {
	if(relayState->relay_state == 1){
		GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
		set_GPIO_state(resp, 13, true);
		free(resp);
	} else if (relayState->relay_state == 0) {
		GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
		set_GPIO_state(resp, 13, false);
		free(resp);
	} else {
		printf("Error while trying to change relay state.\n");
	}
	strcpy(relayState->cmd, "A_REL");
}

void displayMessage (actuator_data_t *lcdState) {
	if(alarm_ == 0){
		changeMessage((lcdState->message));
	}
	strcpy(lcdState->cmd, "A_LCD");
}

void getAlarm(actuator_data_t *alarmState){
	if (alarm_ == 0){
		alarmState->alarm_=0;
	} else {
		alarmState->alarm_=1;
	}
	strcpy(alarmState->cmd, "A_ALA");
}

void getActuatorList(actuator_data_t *actuatorListState){
	strncpy(actuatorListState->actuator_list, "2xLED 1xLCD 1xRLY",(size_t) 18);
	strcpy(actuatorListState->cmd, "R_ACL");
}

void triggerAlarm(actuator_data_t *alarmState){
	if (alarmState->alarm_==0){
		alarm_ = 0;
		GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
		set_GPIO_state(resp, 19, false);
		free(resp);
		changeMessage("Normal operation");
	} else {
		alarm_ = 1;
	}
	strcpy(alarmState->cmd, "A_ALA");
}

void *alarm_function() {
	display_alarm();
	//ledOn (false);
	return NULL;
}

void *lcdDisplay_thread (void *arg){
  struct sensor_data *comp_data =(struct sensor_data*)arg;
  while(1){
    sleep(70);
    if (alarm_ == 0){ 
    	if (wiringPiSetup () == -1) exit (1);
  		wiringPiI2CSetup(I2C_ADDR);
        lcd_start();
        print_sensor_data_(comp_data);
    } else {
      
    }
  }
  
  pthread_exit (0);
}
