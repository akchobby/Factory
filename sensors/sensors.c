/*
 *Author : Anil Kumar Cahvali
 *Basic file to call required sensor functions.
 *
*/

//---------------------------------------------------------
//Headers

#include "sensors.h"



//Raspberry 3B+ platform's default I2C device file
#define IIC_Dev  "/dev/i2c-1"

//---------------------------------------------------------
//
void user_delay_ms(uint32_t period)
{
  usleep(period*1000);
}

//---------------------------------------------------------
//I2C bus read
int8_t user_i2c_read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  write(bme_fd, &reg_addr,1);
  read(bme_fd, data, len);
  return 0;
}

//---------------------------------------------------------
//I2C bus write
int8_t user_i2c_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  int8_t *buf;
  buf = malloc(len +1);
  buf[0] = reg_addr;
  memcpy(buf +1, data, len);
  write(bme_fd, buf, len +1);
  free(buf);
  return 0;
}

//---------------------------------------------------------
//
void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE
	printf("temperature:%0.2f*C   pressure:%0.2fhPa   humidity:%0.2f%%\r\n",comp_data->temperature, comp_data->pressure/100, comp_data->humidity);
#else
	printf("temperature:%ld*C   pressure:%ldhPa   humidity:%ld%%\r\n",comp_data->temperature, comp_data->pressure/100, comp_data->humidity);
#endif
}

//---------------------------------------------------------
//BME sensor get data

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev,struct bme280_data *comp_data)
{
	int8_t rslt;
	uint8_t settings_sel;
	

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	printf("Temperature           Pressure             Humidity\r\n");

	/* Delay while the sensor completes a measurement */
	dev->delay_ms(70);
	rslt = bme280_get_sensor_data(BME280_ALL, comp_data, dev);
	print_sensor_data(comp_data);

	return rslt;
}

//---------------------------------------------------------
//
void initSensors(){
  
  
  int8_t rslt = BME280_OK;

  if ((bme_fd = open(IIC_Dev, O_RDWR)) < 0) {
    printf("Failed to open the i2c bus %d",bme_fd);
    exit(1);
  }
  if (ioctl(bme_fd, I2C_SLAVE, 0x77) < 0) {
    printf("Failed to acquire bus access and/or talk to slave.\n");
    exit(1);
  }
  //dev.dev_id = BME280_I2C_ADDR_PRIM;//0x76
  dev.dev_id = BME280_I2C_ADDR_SEC; //0x77
  dev.intf = BME280_I2C_INTF;
  dev.read = user_i2c_read;
  dev.write = user_i2c_write;
  dev.delay_ms = user_delay_ms;
  rslt = bme280_init(&dev);
  printf("\r\n BME280 Init Result is:%d \r\n",rslt);
  
  }

//---------------------------------------------------------
//Function for periodic task
void *task_bme(struct bme280_data *comp_data)
{
  
  stream_sensor_data_normal_mode(&dev,comp_data);
}

//--------------------------------------------------------------------------
//
#ifdef TEST
int main (int argc ,char **argv){	
	pthread_t thread2;
	int  iret2;
	struct bme280_data comp_data;
	initSensors();
	iret2 = pthread_create( &thread2, NULL, task_bme, &comp_data);


	pthread_join( thread2, NULL);
	
	printf("Thread 2 returns: %d\n",iret2); 
	   
	return 0;
	}
#endif
