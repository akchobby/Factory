#ifndef UNPARSER_H_
#define UNPARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>

#include "sensors.h"
#include "actuators.h"
#include "GPIO.h"

void response_period(sensor_data_t *data, char* buf);
void response_aperiodic_sensor(sensor_data_t *data, char* buf);
void response_aperiodic_actuator(actuator_data_t *data, char* buf);
void response_aperiodic_gpio(GPIO_RESPONSE data, char* buf);


#endif /*UNPARSER_H_*/

