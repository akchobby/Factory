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

// CUSTOM LIBRARIES

#include "FIFO_Stack.h"
#include "packet_storage.h"
#include "sensors.h"

// PREDEFINED VALUES

#define BUFFER_SIZ 256

/* SYNCHRONIZATION MECHANISMS */

// Declare semaphores between IC-FF and FF-EO
sem_t sem_IC_FF, sem_FF_EO, sem_EO_AL; 


/* COMMUNICATION INSTRUMENTS */

// Initialize packet storage as global
PacketStorage pck_s;

// THREAD FUNCTIONS (CAN BE MOVED TO OTHER PLACES)

void* ExecOperation(void *no_arg) {
	// Wait for semaphore to synchronize with FF
	sem_wait(&sem_FF_EO);
	
	return NULL;
}

void* InputComm(void *no_arg) {
	
	// Post the semaphore to allow FF to work
	sem_post(&sem_IC_FF);
	return NULL;
}

void* OutputComm(void *no_arg) {
	
	
	return NULL;
}

/* FIFO STACK AUXILIARY FUNCTIONS MOVED TO OWN FILE */
void* FIFOStack(void *no_arg) {
	char buffer_push[BUFFER_SIZ];
	char buffer_pop[BUFFER_SIZ];
	STACK* stack;
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
		PacketStorage_read(&pck_s, buffer_push); 
		// Push string into stack
		StackPush(stack, buffer_push);
		// Pop first string in stack
		StackPop(stack, buffer_pop);
		// PARSE (write into protected state)
		
		// Post to let the operation execution begin
		sem_post(&sem_FF_EO);
	}
	pthread_exit(NULL);
}

void* SendDataPeriodic(void* period_str) {
	// INICIALIZA LA ESTRUCTURA
	sensor_data_t PSD;
	// INDICA EL COMANDO
	char cmd_name[5] = "S_BCS";
	strcpy(PSD.cmd, cmd_name);
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
		alarm();
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
	PacketStorage_init(&pck_s);
	
	printf("Starting Factory: Creating Threads!\n");
	
	// Create "dummy" thread on InputCommunication (TBM)
	if (pthread_create(&th_IC, NULL, &InputComm, NULL)<0) {
		fprintf (stderr, "pthread_create error for Input Communication\n");    
		exit (1);
	}
	
	// Create "dummy" thread on OutputCommunication (TBM)
	if (pthread_create(&th_IC, NULL, &OutputComm, NULL)<0) {
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
