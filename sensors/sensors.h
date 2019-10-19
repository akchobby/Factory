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

struct bme280_dev dev;
int bme_fd;

void user_delay_ms(uint32_t period);
int8_t user_i2c_read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t user_i2c_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len);
void print_sensor_data(struct bme280_data *comp_data);
int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev,struct bme280_data *comp_data);
void initSensors();
void *task_bme(struct bme280_data *comp_data);



#endif /* SENSORTRY_H_ */
