#include "unparser.h"


void response_period(sensor_data_t *data){
	char unparse[256];
	char cpyvalue[10];
	strcpy(unparse, "cmd:");
	strcat(unparse, data->cmd);
	strcat(unparse, ",Temperature:");
	snprintf(cpyvalue, 6, "%0.2f", data->value[0]);
	strcat(unparse, cpyvalue);
	bzero(cpyvalue, sizeof(cpyvalue));
	strcat(unparse, ",Pressure:");
	snprintf(cpyvalue, 6, "%0.2f", data->value[1]/100);
	strcat(unparse, cpyvalue);
	bzero(cpyvalue, sizeof(cpyvalue));
	strcat(unparse, ",Humidity:");
	snprintf(cpyvalue, 6, "%0.2f", data->value[2]);
	strcat(unparse, cpyvalue);
	printf("%s",unparse);
	}
	
void response_aperiodic_sensor(sensor_data_t *data){
	char unparse[256];
	char cpyvalue[10];
	strcpy(unparse, "cmd:");
	strcat(unparse, data->cmd);
	bzero(cpyvalue, sizeof(cpyvalue));
	if(strcmp(data->cmd, "R_TEV")==0){
		strcat(unparse, ",Temperature:");
		snprintf(cpyvalue, 6, "%0.2f", data->value[0]);
		strcat(unparse, cpyvalue);
		bzero(cpyvalue, sizeof(cpyvalue));
	}else if(strcmp(data->cmd, "R_PRV")==0){
		strcat(unparse, ",Pressure:");
		snprintf(cpyvalue, 6, "%0.2f", data->value[1]);
		strcat(unparse, cpyvalue);
		bzero(cpyvalue, sizeof(cpyvalue));
	}else if(strcmp(data->cmd, "R_HUV")==0){
		strcat(unparse, ",Humidity:");
		snprintf(cpyvalue, 6, "%0.2f", data->value[2]);
		strcat(unparse, cpyvalue);
	}
	printf("%s",unparse);

	//make_packet(unparse);
}

void response_aperiodic_actuator(actuator_data_t *data){
	char unparse[256];
	strcpy(unparse, "Done Actuation");
	printf("%s",unparse);
	//make_packet(unparse);
	
}
void response_aperiodic_gpio(GPIO_RESPONSE *data){
	char unparse[256];
	char cpyvalue[10];
	strcpy(unparse, "cmd:");
	strcat(unparse, data->cmd);
	bzero(cpyvalue, sizeof(cpyvalue));
	if(strcmp(data->cmd, "R_G_GPIO_S")==0){
		strcat(unparse, ",GPIO Num:");
		snprintf(cpyvalue, 6, "%d", (int)data->GPIO_nb);
		strcat(unparse, cpyvalue);
		bzero(cpyvalue, sizeof(cpyvalue));
		strcat(unparse, ",GPIO_state:");
		snprintf(cpyvalue, 6, "%d", (int)data->GPIO_state);
		strcat(unparse, cpyvalue);
		bzero(cpyvalue, sizeof(cpyvalue));
	}else if(strcmp(data->cmd, "R_S_GPIO_S")==0){
		snprintf(cpyvalue, 6, ",GPIO %d set", (int)data->GPIO_nb);
		strcat(unparse, cpyvalue);
		bzero(cpyvalue, sizeof(cpyvalue));
	}else if(strcmp(data->cmd, "R_G_GPIO_D")==0){
		strcat(unparse, ",GPIO Num:");
		snprintf(cpyvalue, 6, "%d", (int)data->GPIO_nb);
		strcat(unparse, cpyvalue);
		bzero(cpyvalue, sizeof(cpyvalue));
		strcat(unparse, ",GPIO_direction:");
		snprintf(cpyvalue, 6, "%d", (int)data->GPIO_direction);
		strcat(unparse, cpyvalue);
		bzero(cpyvalue, sizeof(cpyvalue));	
	}else if(strcmp(data->cmd, "R_S_GPIO_D")==0){
		snprintf(cpyvalue, 6, ",GPIO %d set", (int)data->GPIO_nb);
		strcat(unparse, cpyvalue);
		bzero(cpyvalue, sizeof(cpyvalue));
	}else if(strcmp(data->cmd, "R_S_GPIO_R")==0){
		snprintf(cpyvalue, 6, ",GPIO %d mode set", (int)data->GPIO_nb);
		strcat(unparse, cpyvalue);
	}
	printf("%s",unparse);
}

#ifdef TEST
int main(){
	sensor_data_t data;
	strcpy(data.cmd,"R_TEV");
	data.value[0] = 15;
	response_aperiodic_sensor(&data);
	return 0;
	
	}
#endif

