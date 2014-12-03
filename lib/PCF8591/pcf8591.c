#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>




/* PCF8591 address and max SCL clock frequency */
static const uint8_t PCF8591_ADDR = 0x48;
static const uint8_t TWI_BITRATE = 100000;



/* Constants used to classify a TWI operation as a read or write */
static const uint8_t TWI_WRITE = 0;
static const uint8_t TWI_READ = 1;




/* Initializes all required TWI registers */ 
static void _twi_init(void) {
	TWSR = 0;
	TWBR = (F_CPU / (TWI_BITRATE) - 16) / 2;
	TWCR = (1 << TWEN);
}


/* Sends out a Master START operation over the bus */
static void _twi_start(void) {

	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT)));
}

/* Sends out a Master STOP operation over the bus */
static void _twi_stop(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/* Sends data over the bus  */
static void _twi_write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT)));
}


/* Issues an ACK after a successful read. This is used for multiple reads such as in a loop */
static uint8_t _twi_read_ack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while(!(TWCR & (1 << TWINT)));
	return TWDR;
}

/* Does not issue an ACK after a succesful read. This is used on the last read over the bus */
static uint8_t _twi_read_no_ack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT)));
	return TWDR;
}



/* Function used for public interfacing of the TWI initialization */
void pcf8591_init(void) {
	_twi_init();
}




/* Returns a single analog value from a given PCF8591 channel */
uint8_t pcf8591_analog_read(uint8_t channel) {
	_twi_start();
	_twi_write(PCF8591_ADDR << 1);
    _twi_write(channel);
	_twi_stop();
	_twi_start();
	_twi_write((PCF8591_ADDR << 1 | TWI_READ));
	_twi_read_ack();
	uint8_t result;
	result = _twi_read_no_ack();
	_twi_stop();
	return result;

}

/* Writes an analog value to the single PCF8591 DAC */
void pcf8591_analog_write(uint8_t value) {
	_twi_start();
	_twi_write((PCF8591_ADDR << 1 | TWI_WRITE));
	_twi_write(0x40);
	_twi_write(value);
	_twi_stop();

}