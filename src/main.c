
/* 	

	Example of PCF8591 ADC/DAC usage with an Atmega328p running at 16 MHz. Serial output is piped to stdout
    for easy formatted printing using printf. 

*/

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "serial.h"
#include "pcf8591.h"



/* USART and TWI initialize */ 
void mcu_init(void) {
	usart_initialize();
	stdout = &uart_output;
	_delay_ms(10);
	pcf8591_init();
	printf("PCF8591 initialized.....\n");
}



int main(void)
{

	mcu_init();
	uint8_t value;


	/* Continuously reads analog value from channel 3 and then writes that analog value to the single DAC */
	for(;;) {
		value = pcf8591_analog_read(AI_CH_3);
		pcf8591_analog_write(value);
		printf("Value: %d\n", value);
		_delay_ms(1000);
	}
}
