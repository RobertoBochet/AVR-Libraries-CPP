#include "UART.h"

int main()
{
	uint8_t rxBufferArray[32], txBufferArray[16];
	
	uint32_t a = 0x1A1B1C1D;
	double b = 5.54534;
	uint16_t c[] = {0x1A1B, 0x2A2B, 0x3A3B};
	uint8_t d = 0;
	uint16_t e[3];
	
	UART::Init(103, rxBufferArray, 32, txBufferArray, 16);//UBRR for F_CPU 8MHz Baud 9600
	UART::DoubleSpeedEnabled();
	
	UART::Tx((uint8_t*) &a, sizeof(uint32_t));
	UART::Tx((uint8_t*) &b, sizeof(double));
	UART::Tx((uint8_t*) c, 3 * sizeof(uint16_t));
	
	while(!UART::RxAvailable());
	d = UART::Rx();
	
	while(UART::RxAvailable() < 3 * sizeof(uint16_t));
	UART::Rx((uint8_t*) e, 3 * sizeof(uint16_t));
}