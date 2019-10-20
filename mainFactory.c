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
 */ 

// C LIBRARIES
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>

// CUSTOM LIBRARIES


// PREDEFINED VALUES

// SYNCHRONIZATION MECHANISMS

sem_t sem_IC_FF, sem_FF_EO; 

// COMMUNICATION INSTRUMENTS

// THREAD FUNCTIONS (CAN BE MOVED TO OTHER PLACES)

// MAIN FUNCTION

int main(void) {
	
	// THREAD AND ATTRIBUTE DECLARATION
	pthread_t th_IC, th_OC, th_FF, th_EO, th_SD;
	pthread_attr_t th_at_IC, th_at_OC, th_at_FF, th_at_EO, th_at_SD;
	
	printf("Starting Factory!\nCreating Threads!");
	
	// Create "dummy" thread on InputCommunication (TBM)
	if (pthread_create(&th_IC, NULL, InputComm, NULL)<0) {
		fprintf (stderr, "pthread_create error for Input Communication\n");    
		exit (1);
	}
	
	// Create "dummy" thread on OutputCommunication (TBM)
	if (pthread_create(&th_IC, NULL, OutputComm, NULL)<0) {
		fprintf (stderr, "pthread_create error for Output Communication\n");    
		exit (1);
	}
	
	// Create thread on FIFO Stack
	if (pthread_create(&th_FF, NULL, FIFOStack, NULL)) {
		fprintf (stderr, "pthread_create error for FIFO Stack\n");    
		exit (1);
	}
	
	// Create thread on Operation Execution
	if (pthread_create(&th_EO, NULL, ExecOperation, NULL)) {
		fprintf (stderr, "pthread_create error for Operation Execution\n");    
		exit (1);
	}
	
	// Create the periodic task to periodically retrieve data via another mechanism
	// Inspired on the skeleton code of Youcef Bouchebaba (ONERA) used in 2MAE502!
	struct timespec *timeStructure = malloc(sizeof(struct timespec));
	timeStructure->tv_sec = 5;
	timeStructure->tv_nsec = 0;
	if (pthread_create(&th_SD, NULL, SendDataPeriodic, (void*) timeStructure)<0) {
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
