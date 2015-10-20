#pragma once

#include <avr/io.h>

namespace EEPROM
{
	template <typename T> T Read(uint16_t);//(address)//Restituisce un valore di tipo {T} letto dall'EEPROM all'indirizzo {address}
	template <typename T> void Read(uint16_t, T[], uint16_t);//(address, array, n)//Legge dall'EEPROM {n} valori di tipo {T} all'indirizzo {address} e li inserisce in {array}
	
	template <typename T> void Write(uint16_t, T);//(address, value)//Scrive un valore {value} di tipo {T} nell'EEPROM all'indirizzo {address}
	template <typename T> void Write(uint16_t, T[], uint16_t);//(address, array, n)//Scrive la matrice {array} di tipo {T} di {n} elementi nell'EEPROM all'indirizzo {address} 
}
//Tipi validi per {T}: uintn_t, intn_t, float, double