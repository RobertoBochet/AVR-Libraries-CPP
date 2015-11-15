#pragma once

#include <avr/io.h>

namespace EEPROM
{
	uint8_t Read(uint16_t);//(address)//Restituisce il valore all'indirizzo {address} della EEPROM 
	void Read(uint16_t, uint8_t*, uint16_t);//(address, pointer, n)//Recupera e posiziona nei registri a partire da {pointer} gli {n} ottetti a partire dall'indirizzo {address} della EEPROM
		
	void Write(uint16_t, uint8_t);//(address, value)//Scrive il valore {value} all'indirizzo {address} della EEPROM
	void Write(uint16_t, uint8_t*, uint16_t);//(address, pointer, n)//Scrive gli {n} ottetti a partire dal registro {pointer} nella EEPROM a partire dall'indirizzo {address}
}