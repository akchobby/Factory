/* HEADER FILE FOR GPIO REMOTE CONTROL */

#ifndef _GPIO_h
#define _GPIO_h

typedef struct S_GPIO_RESPONSE {
	
	char cmd[10];
	short GPIO_nb;
	bool GPIO_state;
	bool GPIO_dir;
	short GPIO_intres;
	
} *GPIO_RESPONSE;

void get_GPIO_state(GPIO_RESPONSE GPIO_R, int pin_nb);
void set_GPIO_state(GPIO_RESPONSE GPIO_R, int pin_nb, bool pin_state);
void set_GPIO_dir(GPIO_RESPONSE GPIO_R, int pin_nb, bool pin_dir);
void get_GPIO_dir(GPIO_RESPONSE GPIO_R, int pin_nb);
void set_GPIO_res(GPIO_RESPONSE GPIO_R, int pin_nb, int res_mode);
#endif
