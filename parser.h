#ifndef PARSER_H_
#define PARSER_H_


#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "common.h"

typedef struct parsed_data {
	char cmd[20];
	short GPIO_nb;
	bool GPIO_state;
	bool GPIO_dir;
	short GPIO_intres;
	int led_nb;
	bool led_state;
	bool relay_state;
	int alarm_nb;
	int alarm_state[3];
	int sensor_nb;
	double temp_threshold;
	double pres_threshold;
	double humd_threshold;
	char message[16];
	}parsed_data_t;

parsed_data_t* parse_packet(char *pck);

#endif /*PARSER_H_*/
