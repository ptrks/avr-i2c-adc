#ifndef PCF8591_H
#define PCF8591_H

#include <stdint.h>


/* Available analog channels on PCF8591 */
enum {
	AI_CH_0 = 0,
	AI_CH_1,
	AI_CH_2,
	AI_CH_3
};



/* Initilizes all required TWI hardware for PCF8591 */ 
void pcf8591_init(void);

/* Read a value from one of the PCF8591 analog input channels */
uint8_t pcf8591_analog_read(uint8_t channel);

/* Write a value to the single PCF8591 analog output channel */
void pcf8591_analog_write(uint8_t value);



#endif