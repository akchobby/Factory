#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include "GPIO.h"
#include "sensors.h"
#include "actuators.h"

void requestHandle(parsed_data_t commandData) {
	if(strcmp(commandData->cmd, "S_CMS_D") == 0) {
		
	} else if(strcmp(commandData->cmd, "S_CMS_F") == 0) {
		
	} else if(strcmp(commandData->cmd, "G_SEL") == 0) {
		
	} else if(strcmp(commandData->cmd, "G_TEV") == 0) {
		sensor_data_t *temp = malloc(sizeof(sensor_data_t));
		get_temperature(&temp);
		
	} else if(strcmp(commandData->cmd, "G_PRV") == 0) {
		sensor_data_t *pres = malloc(sizeof(sensor_data_t));
		get_pressure(&pres);
		
	} else if(strcmp(commandData->cmd, "G_HUV") == 0) {
		sensor_data_t *humd = malloc(sizeof(sensor_data_t));
		get_humidity(&humd);
		
	} else if(strcmp(commandData->cmd, "S_TET") == 0) {
		set_temperature_threshold(commandData->temp_threshold, &threshold_data); // should be defined statically on main
		
	} else if(strcmp(commandData->cmd, "S_PRT") == 0) {
		set_pressure_threshold(commandData->pres_threshold, &threshold_data);
		
	} else if(strcmp(commandData->cmd, "S_HUT") == 0) {
		set_humidity_threshold(commandData->humd_threshold, &threshold_data);
		
	} else if(strcmp(commandData->cmd, "G_BME") == 0) {
		sensor_data_t *all;
		get_all(&all);
		
	} else if(strcmp(commandData->cmd, "G_ACL") == 0) {
		actuator_data_t *actList = malloc(sizeof(actuator_data_t));
		getActuatorList(&actList);
		
	} else if(strcmp(commandData->cmd, "S_LED") == 0) {
		actuator_data_t *led_st = malloc(sizeof(actuator_data_t));
		led_st->led_nb = commandData->led_nb;
		led_st->led_state = commandData->led_state;
		changeLedState(&led_st);
		
	} else if(strcmp(commandData->cmd, "S_REL") == 0) {
		actuator_data_t *relay_st = malloc(sizeof(actuator_data_t));
		relay_st_st->relay_state = commandData->relay_state;
		changeRelayState(&relay_st);
		
	} else if(strcmp(commandData->cmd, "S_LCD") == 0) {
		actuator_data_t *lcd_st = malloc(sizeof(actuator_data_t));
		strcpy(lcd_st->message, commandData->message);
		displayMessage(&commandData);
		
	} else if(strcmp(commandData->cmd, "G_ALA") == 0) {
		actuator_data_t *ala_st = malloc(sizeof(actuator_data_t));
		//sem_post(&sem_EO_AL);
		getAlarm(&ala_st);
		
	} else if(strcmp(commandData->cmd, "S_ALA") == 0) {
		sem_post(&sem_EO_AL);
		actuator_data_t *ala_st = malloc(sizeof(actuator_data_t));
		ala_st->alarm = commandData->alarm;
		setAlarm(&ala_st);
		
	} else if(strcmp(commandData->cmd, "G_IOS") == 0) {
		GPIO_RESPONSE *resp = malloc(sizeof(GPIO_RESPONSE));
		get_GPIO_state(&resp, commandData->GPIO_nb);
		
	} else if(strcmp(commandData->cmd, "S_IOS") == 0) {
		GPIO_RESPONSE *resp = malloc(sizeof(GPIO_RESPONSE));
		set_GPIO_state(&resp, commandData->GPIO_nb, commandData->GPIO_state);
		
	} else if(strcmp(commandData->cmd, "G_IOD") == 0) {
		GPIO_RESPONSE *resp = malloc(sizeof(GPIO_RESPONSE));
		set_GPIO_dir(&resp, commandData->GPIO_nb, commandData->GPIO_dir);
		
	} else if(strcmp(commandData->cmd, "S_IOD") == 0) {
		GPIO_RESPONSE *resp = malloc(sizeof(GPIO_RESPONSE));
		get_GPIO_dir(&resp, commandData->GPIO_nb);
		
	} else if(strcmp(commandData->cmd, "S_IOR") == 0) {
		GPIO_RESPONSE *resp = malloc(sizeof(GPIO_RESPONSE));
		set_GPIO_res(&resp, commandData->GPIO_nb, commandData->GPIO_res_mode);
	}
		
}
