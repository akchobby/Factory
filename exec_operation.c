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
	if (strcmp(commandData->cmd, 'G_POR')){
		
	} else if(strcmp(commandData->cmd, 'S_POR')) {
		
	} else if(strcmp(commandData->cmd, 'S_CMC_D')) {
		
	} else if(strcmp(commandData->cmd, 'S_CMC_F')) {
		
	} else if(strcmp(commandData->cmd, 'S_CMS_D')) {
		
	} else if(strcmp(commandData->cmd, 'S_CMS_F')) {
	
	} else if(strcmp(commandData->cmd, 'G_SEL')) {
		
	} else if(strcmp(commandData->cmd, 'G_TEV')) {
		get_temperature(&commandData);
		
	} else if(strcmp(commandData->cmd, 'G_PRV')) {
		get_pressure(&commandData);
		
	} else if(strcmp(commandData->cmd, 'G_HUV')) {
		get_humdity(&commandData);
		
	} else if(strcmp(commandData->cmd, 'G_TET')) {
		get_all(&commandData);
		
	} else if(strcmp(commandData->cmd, 'G_TET')) {
		
	} else if(strcmp(commandData->cmd, 'G_PRT')) {
		
	} else if(strcmp(commandData->cmd, 'G_TET')) {
		
	} else if(strcmp(commandData->cmd, 'G_HUT')) {
		
	} else if(strcmp(commandData->cmd, 'S_TET')) {
		
	} else if(strcmp(commandData->cmd, 'S_PRT')) {
		
	} else if(strcmp(commandData->cmd, 'S_HUT')) {
		
	} else if(strcmp(commandData->cmd, 'G_BME')) {
		
	} else if(strcmp(commandData->cmd, 'G_ACL')) {
		
	} else if(strcmp(commandData->cmd, 'S_LED')) {
		changeLedState(&commandData);
		
	} else if(strcmp(commandData->cmd, 'S_REL')) {
		changeRelayState(&commandData);
		
	} else if(strcmp(commandData->cmd, 'S_LCD')) {
		displayMessage(&commandData);
		
	} else if(strcmp(commandData->cmd, 'G_ALA')) {
		//sem_post(&sem_EO_AL);
		getAlarm(&commandData);
		
	} else if(strcmp(commandData->cmd, 'S_ALA')) {
		sem_post(&sem_EO_AL);
		setAlarm(&commandData);
		
	} else if(strcmp(commandData->cmd, 'G_IOL')) {
		
		
	} else if(strcmp(commandData->cmd, 'G_IOS')) {
		get_GPIO_state(&commandData, commandData->GPIO_nb);
		
	} else if(strcmp(commandData->cmd, 'S_IOS')) {
		set_GPIO_state(&commandData, commandData->GPIO_nb, commandData->GPIO_state);
		
	} else if(strcmp(commandData->cmd, 'G_IOD')) {
		set_GPIO_dir(&commandData, commandData->GPIO_nb, commandData->GPIO_dir);
		
	} else if(strcmp(commandData->cmd, 'S_IOD')) {
		get_GPIO_dir(&commandData, commandData->GPIO_nb);
		
	} else if(strcmp(commandData->cmd, 'S_IOR')) {
		set_GPIO_res(&commandData, commandData->GPIO_nb, commandData->GPIO_res_mode);
	}
		
}
