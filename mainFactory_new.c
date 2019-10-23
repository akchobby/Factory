//#define _POSIX_C_SOURCE >= 199309L
/* MAIN FILE FOR FACTORY HANDLING */

/* INSTRUCTIONS
 * 
 * - Compile with -lpthread !!
 * 
 */ 

/* LIST OF THREADS (TBDEF)
 * 
 * InputComm()
 * OutputComm()
 * FIFOStack()
 * ExecOperation()
 * SendDataPeriod()
 * Alarm()
 */ 

// C LIBRARIES
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <linux/i2c-dev.h>
//#include <unistd.h>

// CUSTOM LIBRARIES

#include "FIFO_Stack.h"
#include "packet_storage.h"
#include "actuators.h"
#include "GPIO.h"
#include "parsed_storage.h"
#include "parser.h"
#include "sensors.h"
#include "bme280.h"

// PREDEFINED VALUES

#define BUFFER_SIZ 256

/* SYNCHRONIZATION MECHANISMS */

// Declare semaphores between IC-FF and FF-EO
sem_t sem_IC_FF, sem_FF_EO, sem_EO_AL; 


/* COMMUNICATION INSTRUMENTS */

// Initialize packet storage as global
PacketStorage pck_s;
ParsedStorage parsed_s;

sensor_threshold_t threshold_data;

// THREAD FUNCTIONS (CAN BE MOVED TO OTHER PLACES)

void* ExecOperation(void *no_arg) {
	parsed_data_t *commandData = malloc(sizeof(parsed_data_t));
	// Wait for semaphore to synchronize with FF
	while(1) {
		sem_wait(&sem_FF_EO);
		ParsedStorage_read(parsed_s, commandData);
		
		if(strcmp(commandData->cmd, "S_CMS_D") == 0) {
		
		} else if(strcmp(commandData->cmd, "S_CMS_F") == 0) {
			
		} else if(strcmp(commandData->cmd, "G_SEL") == 0) {
			
		} else if(strcmp(commandData->cmd, "G_TEV") == 0) {
			sensor_data_t *temp = malloc(sizeof(sensor_data_t));
			get_temperature(temp);
			
		} else if(strcmp(commandData->cmd, "G_PRV") == 0) {
			sensor_data_t *pres = malloc(sizeof(sensor_data_t));
			get_pressure(pres);
			
		} else if(strcmp(commandData->cmd, "G_HUV") == 0) {
			sensor_data_t *humd = malloc(sizeof(sensor_data_t));
			get_humdity(humd);
			
		} else if(strcmp(commandData->cmd, "S_TET") == 0) {
			set_temperature_threshold(commandData->temp_threshold, &threshold_data); // should be defined statically on main
			
		} else if(strcmp(commandData->cmd, "S_PRT") == 0) {
			set_pressure_threshold(commandData->pres_threshold, &threshold_data);
			
		} else if(strcmp(commandData->cmd, "S_HUT") == 0) {
			set_humidity_threshold(commandData->humd_threshold, &threshold_data);
			
		} else if(strcmp(commandData->cmd, "G_BME") == 0) {
			sensor_data_t *all = malloc(sizeof(sensor_data_t));
			get_all(all);
			
		} else if(strcmp(commandData->cmd, "G_ACL") == 0) {
			actuator_data_t *actList = malloc(sizeof(actuator_data_t));
			getActuatorList(actList);
			
		} else if(strcmp(commandData->cmd, "S_LED") == 0) {
			actuator_data_t *led_st = malloc(sizeof(actuator_data_t));
			led_st->led_nb = commandData->led_nb;
			led_st->led_state = commandData->led_state;
			changeLedState(led_st);
			
		} else if(strcmp(commandData->cmd, "S_REL") == 0) {
			actuator_data_t *relay_st = malloc(sizeof(actuator_data_t));
			relay_st->relay_state = commandData->relay_state;
			changeRelayState(relay_st);
			
		} else if(strcmp(commandData->cmd, "S_LCD") == 0) {
			actuator_data_t *lcd_st = malloc(sizeof(actuator_data_t));
			strcpy(lcd_st->message, commandData->message);
			displayMessage(lcd_st);
			
		} else if(strcmp(commandData->cmd, "G_ALA") == 0) {
			actuator_data_t *ala_st = malloc(sizeof(actuator_data_t));
			//sem_post(&sem_EO_AL);
			getAlarm(ala_st);
			
		} else if(strcmp(commandData->cmd, "S_ALA") == 0) {
			sem_post(&sem_EO_AL);
			actuator_data_t *ala_st = malloc(sizeof(actuator_data_t));
			ala_st->alarm_ = commandData->alarm_nb;
			triggerAlarm(ala_st);
			
		} else if(strcmp(commandData->cmd, "G_IOS") == 0) {
			GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
			get_GPIO_state(resp, commandData->GPIO_nb);
			
		} else if(strcmp(commandData->cmd, "S_IOS") == 0) {
			GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
			set_GPIO_state(resp, commandData->GPIO_nb, commandData->GPIO_state);
			
		} else if(strcmp(commandData->cmd, "G_IOD") == 0) {
			GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
			set_GPIO_dir(resp, commandData->GPIO_nb, commandData->GPIO_dir);
			
		} else if(strcmp(commandData->cmd, "S_IOD") == 0) {
			GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
			get_GPIO_dir(resp, commandData->GPIO_nb);
			
		} else if(strcmp(commandData->cmd, "S_IOR") == 0) {
			GPIO_RESPONSE resp = malloc(sizeof(GPIO_RESPONSE));
			set_GPIO_res(resp, commandData->GPIO_nb, commandData->GPIO_intres);
		}
		
		free(commandData);
	}
	
	return NULL;
}

void* InputComm(void *no_arg) {
	
	// Post the semaphore to allow FF to work
	//PacketStorage_write(pck_s, );
	sem_post(&sem_IC_FF);
	return NULL;
}

void* OutputComm(void *no_arg) {
	
	
	return NULL;
}

/* FIFO STACK AUXILIARY FUNCTIONS MOVED TO OWN FILE */
void* FIFOStack(void *no_arg) {
	char *buffer_push = malloc((BUFFER_SIZ+1)*sizeof(char));
	char *buffer_pop = malloc((BUFFER_SIZ+1)*sizeof(char));
	parsed_data_t* genStruct = malloc(sizeof(parsed_data_t));
	STACK* stack = malloc(sizeof(STACK));
	StackInit(stack);
	
	while(1) {
		// Wait for IC to post the packet
		sem_wait(&sem_IC_FF);
		// INTERNAL CODE
		/* - Push the string into stack
		 * - Pop first string in stack, parse
		 * - Write on protected space
		 */ 
		// Store last packet in a buffer
		PacketStorage_read(pck_s, buffer_push); 
		// Push string into stack
		StackPush(stack, buffer_push);
		// Pop first string in stack
		StackPop(stack, buffer_pop);
		// PARSE (write into protected state)
		strcpy(buffer_pop, "cmd:G_PRT");
		genStruct = parse_packet(buffer_pop);
		ParsedStorage_write(parsed_s, genStruct);
		// Post to let the operation execution begin
		sem_post(&sem_FF_EO);
	}
	free(buffer_push);
	free(buffer_pop);
	pthread_exit(NULL);
}

void* SendDataPeriodic(void* period_str) {
	// INICIALIZA LA ESTRUCTURA
	sensor_data_t PSD;
	// INDICA EL COMANDO
	//char cmd_name[5] = "S_BCS";
	strcpy(PSD.cmd, "S_BCS");
	//PSD.cmd = "S_BCS";
	PSD.id = 0;
	// Declare semaphore to make sure the function waits
	sem_t SDP_sem;
	// Declare time structure to store the abs. time
	struct timespec trigger_time;
	struct timespec *period = (struct timespec *) period_str;
	//timeval trigger_time, *period;
	//period->tv_sec = 60;
	// Initialize semaphore
	sem_init(&SDP_sem, 0, 0);
	// Get absolute time into the created timespec struct
	clock_gettime(CLOCK_REALTIME, &trigger_time);
	//gettimeofday(&trigger_time, NULL);
	
	while(1) {
		// UPDATE TIME
		trigger_time.tv_sec += period->tv_sec;
		// WAIT FOR THE INSTANT OF TIME TO BE REACHED
		sem_timedwait(&SDP_sem, &trigger_time);
		// GET ALL VALUES FROM THE SENSOR
		get_all(&PSD);
		// SEND TO DASHBOARDS AND FACTORIES
	}
	pthread_exit(NULL);
}

void* Alarm_Thread(void *no_arg) {
	struct timespec trigger_start;
	struct timespec trigger_end;
	char finished = 0;
	while(1) {
		// WAIT FOR THE SEMAPHORE COMING FROM EXECOPERATION
		sem_wait(&sem_EO_AL);
		clock_gettime(CLOCK_REALTIME, &trigger_start);
		alarm_function();
		while(finished==0) {
			clock_gettime(CLOCK_REALTIME, &trigger_end);
			if (trigger_end.tv_sec >= trigger_start.tv_sec + 60) { 
				finished=1;
			}			
		}
	}
	return NULL;
}

int main(void) {
	
	// THREAD AND ATTRIBUTE DECLARATION
	pthread_t th_IC, th_OC, th_FF, th_EO, th_SD, th_AL;
	//pthread_attr_t th_at_IC, th_at_OC, th_at_FF, th_at_EO, th_at_SD, th_at_AL;
	
	printf("Starting Factory: Setting up communication mechanisms!\n");
	
	// Initialize semaphore between IC-FF
	sem_init(&sem_IC_FF, 1, 0);
	// Initialize semaphore between FF-EO
	sem_init(&sem_FF_EO, 1, 0);
	// Initialize packet storage
	//pck = malloc(sizeof(PacketStorage));
	//PacketStorage_init(&pck_s);
	
	pck_s = PacketStorage_init();
	// Initialize parsed storage
	//parsed_s = ParsedStorage_init();
	parsed_s = ParsedStorage_init();
	
	printf("Starting Factory: Creating Threads!\n");
	
	// Create "dummy" thread on InputCommunication (TBM)
	if (pthread_create(&th_IC, NULL, &InputComm, NULL)<0) {
		fprintf (stderr, "pthread_create error for Input Communication\n");    
		exit (1);
	}
	
	// Create "dummy" thread on OutputCommunication (TBM)
	if (pthread_create(&th_OC, NULL, &OutputComm, NULL)<0) {
		fprintf (stderr, "pthread_create error for Output Communication\n");    
		exit (1);
	}
	
	// Create thread on FIFO Stack
	if (pthread_create(&th_FF, NULL, &FIFOStack, NULL)) {
		fprintf (stderr, "pthread_create error for FIFO Stack\n");    
		exit (1);
	}
	
	// Create thread on Operation Execution
	if (pthread_create(&th_EO, NULL, &ExecOperation, NULL)) {
		fprintf (stderr, "pthread_create error for Operation Execution\n");    
		exit (1);
	}
	
	// Create thread on Alarm
	if (pthread_create(&th_AL, NULL, &Alarm_Thread, NULL)) {
		fprintf (stderr, "pthread_create error for Alarm\n");    
		exit (1);
	}
	
	// Create the periodic task to periodically retrieve data via another mechanism
	// Inspired on the skeleton code of Youcef Bouchebaba (ONERA) used in 2MAE502!
	struct timespec *timeStructure = malloc(sizeof(struct timespec));
	timeStructure->tv_sec = 5;
	timeStructure->tv_nsec = 0;
	if (pthread_create(&th_SD, NULL, &SendDataPeriodic, (void*) timeStructure)<0) {
		fprintf (stderr, "pthread_create error for Periodic Data Sending\n");    
		exit (1);
	}
	
	
	// Join threads again to guarantee orderly exit
	pthread_join(th_IC,0);
	pthread_join(th_OC,0);
	pthread_join(th_FF,0);
	pthread_join(th_EO,0);
	pthread_join(th_SD,0);
	
	return 0;
}
