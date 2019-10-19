#include <stdlib.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include <string.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <pthread.h>
#include "bme280.h"
#include "i2clcd.h"

void ledOn (int led_nb);
void ledOff (int led_nb);
void relayHigh ();
void relayLow ();

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
  // llamar a la funcion de joan gpio
}

void ledOff (int led_nb) {
  // llamar a la funcion de joan gpio
}

void relayHigh () {
  // llamar a la funcion de joan gpio
}

void relayLow () {
  // llamar a la funcion de joan gpio
}

void *lcdDisplay_thread (void *arg){
  struct bme280_data *comp_data =(struct bme280_data*)arg;
  while(1){
    sleep(70);
    if ((*comp_data).alarm == 0){ 
      print_sensor_data(comp_data);
    } else {
      display_alarm();
      // led_alarm();
    }
  }
  
  pthread_exit (0);
}
