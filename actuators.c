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

// Define some device parameters
#define I2C_ADDR   0x27 // I2C device address

int alarm = 0;

void changeLedState (parsed_data_t *ledState);
void changeRelayState (parsed_data_t *relayState);
void displayMessage (parsed_data_t *lcdState);
void triggerAlarm(int alarmState);
void *alarm_function(void *arg);
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
		set_GPIO_state(GPIO_nb, true);
	} else if (ledState->led_state == 0) {
		set_GPIO_state(GPIO_nb, false);
	} else {
		printf("Error while trying to change LED state.\n");
	}
	strcpy(ledState->cmd, "A_LED");
}

void changeRelayState (actuator_data_t *relayState) {
	if(relayState->relay_state == 1){
		set_GPIO_state(13, true);
	} else if (ledState->relay_state == 0) {
		set_GPIO_state(13, false);
	} else {
		printf("Error while trying to change relay state.\n");
	}
	strcpy(relayState->cmd, "A_REL");
}

void displayMessage (actuator_data_t *lcdState) {
	if(alarm == 0){
		changeMessage(&(lcdState->message));
	}
	strcpy(lcdState->cmd, "A_LCD");
}

void getAlarm(actuator_data_t *alarmState){
	if (alarm_state == 0){
		alarmState->alarm==0
	} else {
		alarmState->alarm==1
	}
	strcpy(lcdState->cmd, "A_ALA");
}

void getActuatorList(actuator_data_t *actuatorListState){
	actuatorListState->*actuator_list[] = {"2xLED", "1xLCD", "1xRLY"};
	strcpy(lcdState->cmd, "R_ACL");
}

void triggerAlarm(actuator_data_t *alarmState){
	if (alarmState->alarm==0){
		alarm_state = 0;
		set_GPIO_state(19, false);
		changeMessage("Normal operation");
	} else {
		alarm_state = 1;
	}
	strcpy(lcdState->cmd, "A_ALA");
}

void *alarm_function(void *arg) {
	display_alarm();
	ledOn (false);
}

void *lcdDisplay_thread (void *arg){
  struct sensor_data *comp_data =(struct sensor_data*)arg;
  while(1){
    sleep(70);
    if (alarm == 0){ 
    	if (wiringPiSetup () == -1) exit (1);
  		fd = wiringPiI2CSetup(I2C_ADDR);
        lcd_start();
        print_sensor_data(comp_data);
    } else {
      
    }
  }
  
  pthread_exit (0);
}


