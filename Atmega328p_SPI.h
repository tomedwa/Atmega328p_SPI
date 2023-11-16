// NEED HEADER

#ifndef ATMEGA328P_SPI_H_
#define ATMEGA328P_SPI_H_

#define SS		2
#define MOSI	3
#define MISO	4
#define SCK		5

#define SS_HIGH A328p_set_SS(1)
#define SS_LOW	A328p_set_SS(0)

void A328p_set_SS(uint8_t value);
void A328p_SPI_init();
void A328p_SPI_transfer_data_to_reg(uint8_t reg, uint8_t data);
void A328p_SPI_transfer_data_only(uint8_t data);
uint8_t A328p_SPI_receive_from_reg(uint8_t reg);
void A328p_SPI_send_reg_only(uint8_t reg); // also for multibyte reads n shit
uint8_t A328p_SPI_receive_data_only();	// good for multibyte reads

#endif /* ATMEGA328P_SPI_H_ */