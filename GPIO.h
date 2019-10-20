/* HEADER FILE FOR GPIO REMOTE CONTROL */

#ifndef _GPIO_h
#define _GPIO_h

typedef struct GPIO_RESPONSE GPIO_RESPONSE;

void get_GPIO_state(int pin_nb);
void set_GPIO_state(int pin_nb, bool pin_state);
void set_GPIO_dir(int pin_nb, bool pin_dir);
void get_GPIO_dir(int pin_nb);
void set_GPIO_res(int pin_nb, int res_mode);
#endif
