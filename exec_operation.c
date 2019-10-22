#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include "GPIO.h"
#include "sensors.h"

void requestHandle(parsed_data_t commandData) {
	if (strcmp(commandData->cmd, "G_POR") == 0){
		
	} else if(strcmp(commandData->cmd, "S_POR") == 0) {
		
	} else if(strcmp(commandData->cmd, "S_CMC_D") == 0) {
		
	} else if(strcmp(commandData->cmd, "S_CMC_F") == 0) {
		
	} else if(strcmp(commandData->cmd, "S_CMS_D") == 0) {
		
	} else if(strcmp(commandData->cmd, "S_CMS_F") == 0) {
	
	} else if(strcmp(commandData->cmd, "G_SEL") == 0) {
		
	} else if(strcmp(commandData->cmd, "G_TEV") == 0) {
		get_temperature(&commandData);
		
	} else if(strcmp(commandData->cmd, "G_PRV") == 0) {
		get_pressure(&commandData);
		
	} else if(strcmp(commandData->cmd, "G_HUV") == 0) {
		get_humdity(&commandData);
		
	} else if(strcmp(commandData->cmd, "S_TET") == 0) {
		set_temperature_threshold(commandData->temp_threshold, &commandData);
		
	} else if(strcmp(commandData->cmd, "S_PRT") == 0) {
		set_pressure_threshold(commandData->pres_threshold, &commandData)
		
	} else if(strcmp(commandData->cmd, "S_HUT") == 0) {
		set_pressure_threshold(commandData->hum_threshold, &commandData)
		
	} else if(strcmp(commandData->cmd, "G_BME") == 0) {
		get_all(&commandData);
		
	} else if(strcmp(commandData->cmd, "G_ACL") == 0) {
		getActuatorList(&commandData);
		
	} else if(strcmp(commandData->cmd, "S_LED") == 0) {
		changeLedState(&commandData);
		
	} else if(strcmp(commandData->cmd, "S_REL") == 0) {
		changeRelayState(&commandData);
		
	} else if(strcmp(commandData->cmd, "S_LCD") == 0) {
		displayMessage(&commandData);
		
	} else if(strcmp(commandData->cmd, "G_ALA") == 0) {
		//sem_post(&sem_EO_AL);
		getAlarm(&commandData);
		
	} else if(strcmp(commandData->cmd, "S_ALA") == 0) {
		sem_post(&sem_EO_AL);
		setAlarm(&commandData);
		
	} else if(strcmp(commandData->cmd, "G_IOS") == 0) {
		get_GPIO_state(&commandData, commandData->GPIO_nb);
		
	} else if(strcmp(commandData->cmd, "S_IOS") == 0) {
		set_GPIO_state(&commandData, commandData->GPIO_nb, commandData->GPIO_state);
		
	} else if(strcmp(commandData->cmd, "G_IOD") == 0) {
		set_GPIO_dir(&commandData, commandData->GPIO_nb, commandData->GPIO_dir);
		
	} else if(strcmp(commandData->cmd, "S_IOD") == 0) {
		get_GPIO_dir(&commandData, commandData->GPIO_nb);
		
	} else if(strcmp(commandData->cmd, "S_IOR") == 0) {
		set_GPIO_res(&commandData, commandData->GPIO_nb, commandData->GPIO_res_mode);
	}
		
}
