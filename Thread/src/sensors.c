/*
 *Author : Anil Kumar Chavali
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
void print_sensor_data(sensor_data_t *comp_data)
{
  
  switch(comp_data->id){
    case 3: printf("temperature:%0.2f*C   pressure:%0.2fhPa   humidity:%0.2f%%\r\n",comp_data->value[0], comp_data->value[1]/100, comp_data->value[2]);
	    break;
	    
    case 2: printf("humidity:%0.2f%%\r\n",comp_data->value[2]);
	    break;
	    
    case 1: printf("pressure:%0.2fhPa\n",comp_data->value[1]/100); 
	    break;
	    
    case 0: printf("temperature:%0.2f*C\n",comp_data->value[0]); 
	    break;
	    
    default: printf("ERROR: Check connections");
	    break;
	    
	  }


}

//---------------------------------------------------------
//BME sensor get data

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev)
{
	int8_t rslt;
	uint8_t settings_sel;
	

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;
	
	settings_sel = BME280_ALL_SETTINGS_SEL;

	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	//printf("Temperature           Pressure             Humidity\r\n");

	/* Delay while the sensor completes a measurement */
	dev->delay_ms(70);
	rslt = bme280_get_sensor_data(BME280_ALL, &all_data, dev);
	//print_sensor_data(&all_data);

	return rslt;
}

//---------------------------------------------------------
//Check Alarm

void checkThreshold(sensor_data_t *data, sensor_threshold_t *limits,int *Alarm){

  if(data->id != 3){
    if((data->value[data->id]) > (limits->threshold[data->id])){
      Alarm[data->id] = 1;
      //triggerAlarm();
      }
    }else{
	for(int i=0; i<3 ; i++){
	  if((data->value[i]) > (limits->threshold[i])){
	    Alarm[i] = 1;
	    
	    //triggerAlarm();
	  }
	}
      }
}

//---------------------------------------------------------
//
void initBme(){
  
  
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
//Getters Sensor Vals

void get_temperature(sensor_data_t *temp){
	
	temp->id = 0;
	strcpy(temp->cmd, "R_TEV");
  
	initBme();
	stream_sensor_data_normal_mode(&dev);
	temp->value[temp->id] = all_data.temperature;
	
	
	
}

void get_pressure(sensor_data_t *pres){
  
	pres->id = 1;
	strcpy(pres->cmd, "R_PRV");

	initBme();
	stream_sensor_data_normal_mode(&dev);
	pres->value[1] = all_data.pressure;
	
	
}

void get_humdity(sensor_data_t *humd){
  
	humd->id = 2;
	strcpy(humd->cmd, "R_HUV");
    
	initBme();
	stream_sensor_data_normal_mode(&dev);
	humd->value[2]  = all_data.humidity;
	
}

void get_all(sensor_data_t *data){
  
	data->id = 3;
	strcpy(data->cmd, "P_DATA");
	
	initBme();
	stream_sensor_data_normal_mode(&dev);
	data->value[0] = all_data.temperature;
	data->value[1] = all_data.pressure;
	data->value[2]  = all_data.humidity;
	
	
}

void get_sensor_list(sensor_data_t *data){
  strcpy(data->cmd, "R_SEL");
  strncpy(data->list,"BME280(Temp,Pres,Humid)",(size_t)24);
  }

//---------------------------------------------------------
//setters Sensor Thresholds
void set_temperature_threshold(double value, sensor_threshold_t *threshold_data){
  threshold_data->threshold[0] = value;
}

void set_pressure_threshold(double value, sensor_threshold_t *threshold_data){
  threshold_data->threshold[1] = value;
}

void set_humidity_threshold(double value, sensor_threshold_t *threshold_data){
  threshold_data->threshold[2] = value;
}


//---------------------------------------------------------
//Function for periodic task

#ifdef TEST
void *task_bme(sensor_data_t *data)
{
  int i;
  int alarm[3] ={0,0,0};
  sensor_threshold_t thres;
  set_temperature_threshold(21,&thres);
  set_pressure_threshold(100,&thres);
  set_humidity_threshold(50,&thres);
  while(i<10){
    get_all(data);
    checkThreshold(data,&thres, alarm);
    for(int j =0;j<3;j++){
      printf("Alarm %d is %d",j,alarm[j]);
      }
    print_sensor_data(data);
    //get_pressure(data);
    i++;
  }
  
}
//--------------------------------------------------------------------------
//
int main (int argc ,char **argv){	
	pthread_t thread2;
	int  iret2;
	
      
	sensor_data_t sense_data;
      
	iret2 = pthread_create( &thread2, NULL, task_bme,&sense_data);

	
	pthread_join( thread2, NULL);
	
	printf("Thread 2 returns: %d\n",iret2); 
	
	printf("%s \n", sense_data.cmd);
	   
	return 0;
	}
#endif
