#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <string.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include "bme280.h"
#include "i2clcd.h"
#include "GPIO.h"

// Define some device parameters
#define I2C_ADDR   0x27 // I2C device address

void ledOn (int led_nb);
void ledOff (int led_nb);
void relayHigh (void);
void relayLow (void);

#ifdef TEST
int main(struct bme280_data *comp_data, int * alarm_state){
  //pthread_t th_LCD;
  //void *ret;
  
  //if (pthread_create (&th_LCD, NULL, lcdDisplay_thread, comp_data) < 0) {
    //fprintf (stderr, "pthread_create error for thread 1\n");
    //exit (1);
  //}
  
  //(void)pthread_join (th1, &ret);
  
}
#endif

void ledOn (int led_nb) {
	if (led_nb == 1){
  	set_GPIO_state(19, true);
	} else if (led_nb == 2) {
		set_GPIO_state(26, true);
	} else {
		printf("Error while trying to change LED state.\n");
	}
}

void ledOff (int led_nb) {
  if (led_nb == 1){
  	set_GPIO_state(19, false);
	} else if (led_nb == 2) {
		set_GPIO_state(26, false);
	} else {
		printf("Error while trying to change LED state.\n");
	}
}

void relayHigh () {
  set_GPIO_state(13, true);
}

void relayLow () {
  set_GPIO_state(13, false);
}

void *lcdDisplay_thread (void *arg){
  struct bme280_data *comp_data =(struct bme280_data*)arg;
  while(1){
    sleep(70);
    if ((*comp_data).alarm == 0){ 
    	if (wiringPiSetup () == -1) exit (1);
  		fd = wiringPiI2CSetup(I2C_ADDR);
      lcd_start();
      print_sensor_data(comp_data);
    } else {
      display_alarm();
    }
  }
  
  pthread_exit (0);
}


