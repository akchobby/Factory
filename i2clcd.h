#ifndef _i2clcd_h
#define _i2clcd_h

#include <sensors.h>

void lcd_start(void);
void lcd_init(void);
void lcd_byte(int, int);
void lcd_toggle_enable(int);
void print_sensor_data_(sensor_data_t *);
void display_alarm(void);
void typeInt(int);
void typeFloat(float);
void lcdLoc(int);
void ClrLcd(void);
void typeln(const char *);
void typeChar(char);
void changeMessage(char *);

#endif
