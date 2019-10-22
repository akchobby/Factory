#ifndef UNPARSER_H_
#define UNPARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "sensors.h"
//#include "actuators.h"
//#include "GPIO.h"

void response_period(sensor_data_t *data);
void response_aperiodic_sensor(sensor_data_t *data);
//void response_aperiodic_actuator(actuator_data_t *data);
//void response_aperiodic_gpio(GPIO_RESPONSE *data);


#endif /*UNPARSER_H_*/
