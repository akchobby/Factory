#ifndef SENSORS_H_
#define SENSORS_H_

#include "bme280.h"
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>





typedef struct sensor_data{
	int id;
	char cmd[10];
	double value[3];
}sensor_data_t;

typedef struct sensor_threshold{
	double threshold[3];
	}sensor_threshold_t;


struct bme280_dev dev;
int bme_fd;
struct bme280_data all_data;


void user_delay_ms(uint32_t period);
int8_t user_i2c_read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t user_i2c_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len);
void print_sensor_data(sensor_data_t*comp_data);
int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev);
void initBme();

void checkThreshold(sensor_data_t *data, sensor_threshold_t *limits,int *Alarm);

void get_temperature(sensor_data_t *temp);
void get_pressure(sensor_data_t *pres);
void get_humdity(sensor_data_t *humd);
void get_all(sensor_data_t *data);

void set_humidity_threshold(double value, sensor_threshold_t *threshold_data);
void set_pressure_threshold(double value, sensor_threshold_t *threshold_data);
void set_temperature_threshold(double value, sensor_threshold_t *threshold_data);

void *task_bme(sensor_data_t *comp_data);



#endif /* SENSORTRY_H_ */
