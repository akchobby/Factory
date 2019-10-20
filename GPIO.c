/* FUNCTIONS TO CONTROL THE GPIO, BOTH LOCALLY AND REMOTELY */

/* INSTRUCTIONS:
	Created employing the WiringPi library. 
	Make sure you compile adding -lwiringPi in your Makefile.
*/

/* FUNCTIONS:
 * get_GPIO_state (HIGH OR LOW)
 * set_GPIO_state (HIGH OR LOW)
 * get_GPIO_dir (IN OR OUT)
 * set_GPIO_dir (IN OR OUT)
 * set_GPIO_res (UP / DOWN / NONE)
*/

#include <wiringPi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GPIO_RESPONSE {
	char cmd[10];
	short GPIO_nb;
	bool GPIO_state;
	bool GPIO_dir;
	short GPIO_intres;
};

void get_GPIO_state(int pin_nb);
void set_GPIO_state(int pin_nb, bool pin_state);
void set_GPIO_dir(int pin_nb, bool pin_dir);
void get_GPIO_dir(int pin_nb);

struct GPIO_RESPONSE GPIO_R;

/*int main() {
	
	//get_GPIO_state(0);
	//printf("Result: %d %d\n", GPIO_R.GPIO_state, GPIO_R.GPIO_dir);
	get_GPIO_dir(1);
	get_GPIO_dir(7); 
	
	return 0;
}*/

void get_GPIO_state(int pin_nb) {
	
	// Initialize the wiringPi library
	wiringPiSetupGpio();
	
	// Read the value of the pin, write in the structure
	GPIO_R.GPIO_state = (bool) digitalRead(pin_nb);
	
	GPIO_R.cmd = "R_G_GPIO_S";
	
}

void set_GPIO_state(int pin_nb, bool pin_state) {
	
	// Initialize the wiringPi library
	wiringPiSetupGpio();
	
	// Read the value of the pin, write in the structure
	if (pin_state == 0) {
		
		digitalWrite(pin_nb, LOW);
		
	} else {
		
		digitalWrite(pin_nb, HIGH);
		
	}
	
	GPIO_R.GPIO_state = (bool) digitalRead(pin_nb);
	
	GPIO_R.cmd = "R_S_GPIO_S";
	
}

void get_GPIO_dir(int pin_nb) {
	
	// Export the pin
	char cmd1[50], cmd3[50], cmd4[50], cmd5[50], cmd6[50], cmd7[50], resp[3];
	char cmd2[3]; 
	char command1[100];
	char command2[100];
	char command3[100];
	
	
	strcpy(cmd1, "echo ");
	strcpy(cmd3, " >/sys/class/gpio/export");
	strcpy(cmd4, " >/sys/class/gpio/unexport");
	strcpy(cmd5, "cat ");
	strcpy(cmd6, "/sys/class/gpio/gpio");
	strcpy(cmd7, "/direction");
	
	if (pin_nb < 10) {
	
		snprintf(cmd2, 2, "%d", pin_nb);
		
	} else {
		
		snprintf(cmd2, 3, "%d", pin_nb);
		
	}
	
	strcpy(command1, cmd1);
	strcat(command1, cmd2);
	strcat(command1, cmd3);
	
	strcpy(command2, cmd5);
	strcat(command2, cmd6);
	strcat(command2, cmd2);
	strcat(command2, cmd7);
	
	strcpy(command3, cmd1);
	strcat(command3, cmd2);
	strcat(command3, cmd4);
	
	
	system(command1);
	FILE* fp = popen(command2, "r");
	fscanf(fp,"%s", resp);
	pclose(fp);
	system(command3);
	
	
	if (strcmp(resp,"in")==1) {
		GPIO_R.GPIO_dir = (bool) 1;
	} else {
		GPIO_R.GPIO_dir = (bool) 0;
	}
	
	
	GPIO_R.cmd = "R_G_GPIO_D";
	
}

void set_GPIO_dir(int pin_nb, bool pin_dir) {
	
	// Initialize the wiringPi library
	wiringPiSetupGpio();
	
	// Read the value of the pin, write in the structure
	if (pin_dir == 0) {
		
		pinMode(pin_nb, OUTPUT);
		
	} else {
		
		pinMode(pin_nb, INPUT);
		
	}
	
	// Call get_GPIO_dir but don't write o
	get_GPIO_dir(pin_nb);
	
	GPIO_R.cmd = "R_S_GPIO_D";
	
}

void set_GPIO_res(int pin_nb, int res_mode) {
	
	// Initialize the wiringPi library
	wiringPiSetupGpio();
	
	// Read the value of the pin, write in the structure
	if (res_mode == 0) {
		
		pullUpDnControl(pin_nb, PUD_DOWN);
		
	} else if (res_mode == 1) {
		
		pullUpDnControl(pin_nb, PUD_UP);
		
	} else {
		
		pullUpDnControl(pin_nb, PUD_OFF);
		
	}
	
	GPIO_R.GPIO_intres = (short) res_mode;
	
	GPIO_R.cmd = "R_S_GPIO_R";
	
}
