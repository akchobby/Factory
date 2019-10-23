#include "parser.h"


parsed_data_t* parse_packet(char* pck){
	parsed_data_t data;
	data.alarm_state[0] =0;
	data.alarm_state[1] =0;
	data.alarm_state[2] =0;
	parsed_data_t* dashboardCmd = malloc(sizeof(parsed_data_t));
	//char buffer[257];
	#ifdef TEST
	//strncpy(buffer, "cmd:G_IOS, threshold:26",sizeof(buffer) -1);
	#else
	//strncpy(buffer, pck, (size_t) 257);
	#endif
	char *p;
	p = strtok(pck, " :, ");

	p = strtok(NULL, " :, ");

	strncpy(data.cmd,p,sizeof(data.cmd)); 
	if(strcmp(data.cmd, "G_SEL") == 0) {
		
	} else if(strcmp(data.cmd, "G_TEV") == 0) {

		
	} else if(strcmp(data.cmd, "G_PRV") == 0) {

		
	} else if(strcmp(data.cmd, "G_HUV") == 0) {

		
	} else if(strcmp(data.cmd, "G_TET")==0) {
		
		data.sensor_nb = 0;
		
	} else if(strcmp(data.cmd, "G_PRT")==0) {
		data.sensor_nb = 1;
		
	} else if(strcmp(data.cmd, "G_HUT")==0) {
		data.sensor_nb = 2;
		
	} else if(strcmp(data.cmd, "S_TET")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		//State
		double thresh;
		sscanf(p,"%lf",&thresh);
		data.temp_threshold = thresh;
		
	} else if(strcmp(data.cmd, "S_PRT")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		//State
		double thresh;
		sscanf(p,"%lf",&thresh);
		data.pres_threshold = thresh;
		
	} else if(strcmp(data.cmd, "S_HUT")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		//State
		double thresh;
		sscanf(p,"%lf",&thresh);
		data.humd_threshold = thresh;
		
		printf("%lf", data.humd_threshold);
		
	} else if(strcmp(data.cmd, "G_BME")==0) {
		
		
	} else if(strcmp(data.cmd, "G_ACL")==0) {
		
	} else if(strcmp(data.cmd, "S_LED")==0) {
		
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		int nb;
		sscanf(p,"%d",&nb);
		data.led_nb = nb;
		//State
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}

		int state;
		sscanf(p,"%d",&state);
		data.led_state = (bool)state;
		


		
	} else if(strcmp(data.cmd, "S_REL")==0) {
		//ID
		for(int i = 0;i<4;i++){
		p = strtok(NULL, " :, ");
		}
		//State
		int state;
		sscanf(p,"%d",&state);
		data.relay_state = (bool)state;
		
	
		
	} else if(strcmp(data.cmd, "S_LCD")==0) {
		
		
	} else if(strcmp(data.cmd, "G_ALA")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		
		int nb;
		sscanf(p,"%d",&nb);
		data.alarm_nb= nb;
		
	} else if(strcmp(data.cmd, "S_ALA")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		
		int nb;
		sscanf(p,"%d",&nb);
		
		//State
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		int state;
		sscanf(p,"%d",&state);
		data.alarm_state[nb] = state;

		
		
	
		
	} else if(strcmp(data.cmd, "G_IOS")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		
		int nb;
		sscanf(p,"%d",&nb);
		data.GPIO_nb = (short)nb;
		printf("%d",data.GPIO_nb);

		
		
	}  else if(strcmp(data.cmd, "G_IOD")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		
		int nb;
		sscanf(p,"%d",&nb);
		data.GPIO_nb = (short)nb;
		
		
		
	} else if(strcmp(data.cmd, "S_IOR")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		
		int nb;
		sscanf(p,"%d",&nb);
		data.GPIO_nb = (short)nb;
		//Direction
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		int state;
		sscanf(p,"%d",&state);
		data.GPIO_intres = (short) state;

	}else if(strcmp(data.cmd, "S_IOS")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		
		int nb;
		sscanf(p,"%d",&nb);
		data.GPIO_nb = (short)nb;
		//State
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		int state;
		sscanf(p,"%d",&state);
		data.GPIO_state = (bool) state;
	}else if(strcmp(data.cmd, "S_IOD")==0) {
		//ID
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		
		int nb;
		sscanf(p,"%d",&nb);
		data.GPIO_nb = (short)nb;
		//State
		for(int i = 0;i<2;i++){
		p = strtok(NULL, " :, ");
		}
		int state;
		sscanf(p,"%d",&state);
		data.GPIO_dir = (short) state;
		
	}
	

	return dashboardCmd;
	 
	}
#ifdef TEST
int main(){
	packet_t pck;
	free(parse_packet(pck));
	return 0;
	
	}
#endif
