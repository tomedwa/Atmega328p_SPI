// NEED HEADER
#include <avr/io.h>
#include "Atmega328p_SPI.h"

// Need function comment
void A328p_set_SS(uint8_t value) {
	switch(value) {
		case 0:
			PORTB &= ~(1 << SS);
			return;
		case 1:
			PORTB |= (1 << SS);
			return;
	}
}

// Need function comment
void A328p_SPI_init() {
	DDRB |= (1 << SS) | (1 << MOSI) | (1 << SCK);
	DDRB &= ~(1 << MISO);
	
	SS_LOW;
	
	// Set as master, SPI enable, CPOL=1, CPHA=1, clock rate F_CPU/16 -> clock rate = 500kHz
	SPCR |= (1<<MSTR) | (1<<SPE) | (1<<CPOL) | (1<<CPHA) | (1<<SPR0);
	
	SPSR &= ~(1<<SPI2X); // double clock rate set to ZERO. (ie do not double clockrate).
	
	DDRB |= (1<<MOSI) | (1<<SCK); // set MOSI, SCK as outputs
	
	DDRB &= ~(1<<MISO); // MISO input
	
	SS_HIGH;
}

// Need function comment
void A328p_SPI_transfer_data_to_reg(uint8_t reg, uint8_t data) {
	SS_LOW;
	
	// Send the register address
	SPDR = reg;
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
	// Send the data
	SPDR = data;
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
	
	SS_HIGH;
}

// Need function comment
void A328p_SPI_transfer_data_only(uint8_t data) {
	SS_LOW;
	// Send the data
	SPDR = data;
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
	SS_HIGH;
}

// Need function comment
uint8_t A328p_SPI_receive_from_reg(uint8_t reg) {
	uint8_t data;
	
	SS_LOW;
	
	// Send the register address
	SPDR = reg;
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
	
	// Send dummy data
	SPDR = 0xFF;
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
	
	// This should be the contents of the reg.
	data = SPDR;
	
	SS_HIGH;
	
	return data;
}

// Need function comment
void A328p_SPI_send_reg_only(uint8_t reg) {
	SPDR = reg;
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
}

// Need function comment
uint8_t A328p_SPI_receive_data_only() {
	uint8_t data;
	SPDR = 0x00;
	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));
	
	// This should be the contents of the reg.
	data = SPDR;
	return data;
}