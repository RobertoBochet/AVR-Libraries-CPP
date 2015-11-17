#pragma once

#include <avr/io.h>

namespace EEPROM
{
	uint8_t Read(uint16_t);//(address)//Restituisce il valore all'indirizzo {address} della EEPROM 
	void Read(uint16_t, uint8_t[], uint16_t);//(address, array, n)//Recupera e inserisce in {array} {n} byte dalla EEPROM a partire dall'indirizzo {address}
		
	void Write(uint16_t, uint8_t);//(address, value)//Scrive il valore {value} all'indirizzo {address} della EEPROM
	void Write(uint16_t, uint8_t[], uint16_t);//(address, array, n)//Scrive {n} byte dall'array {array} dalla EEPROM a partire dall'indirizzo {address}
}