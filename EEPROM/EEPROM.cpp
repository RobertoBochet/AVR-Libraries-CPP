#include "EEPROM.h"

uint8_t EEPROM::Read(uint16_t address)
{
	while(EECR & (1 << EEPE));//Attendo che il bit EEPE venga posto a 0 per segnalare che non vi sono procedure in corso sull'EEPROM
	while(SPMCSR & 1);//Attendo che il bit SPMEN venga posto a 0
	
	EEAR = address;//Inserisco l'indirizzo del dato da recuperare in EEAR

	EECR |= (1 << EERE);//Imposto il bit EERE a 1 per avviare la procedura di lettura
	
	return EEDR;//Restituisco il valore letto
}
void EEPROM::Read(uint16_t address, uint8_t* pointer, uint16_t n)
{
	for(; n > 0; n--)
	{
		while(EECR & (1 << EEPE));//Attendo che il bit EEPE venga posto a 0 per segnalare che non vi sono procedure in corso sull'EEPROM
		while(SPMCSR & 1);//Attendo che il bit SPMEN venga posto a 0
		
		EEAR = address;//Inserisco l'indirizzo del dato da recuperare in EEAR
		
		EECR |= (1 << EERE);//Imposto il bit EERE a 1 per avviare la procedura di lettura
		
		*pointer = EEDR;//Attribuisco al byte corrente il valore letto
		
		address++;//Avanzo di un byte nell'indirizzo dell'EEPROM
		pointer++;//Avanzo di un byte nell'indirizzo del valore da leggere
	}
}

void EEPROM::Write(uint16_t address, uint8_t value)
{
	while(EECR & (1 << EEPE));//Attendo che il bit EEPE venga posto a 0 per segnalare che non vi sono procedure in corso sull'EEPROM
	while(SPMCSR & 1);//Attendo che il bit SPMEN venga posto a 0
	
	EEAR = address;//Inserisco l'indirizzo del dato da scrivere in EEAR
	EEDR = value;//Inserisco il dato da scrivere in EEDR
	
	EECR |= (1 << EEMPE);//Imposto il bit EEMPE a 1 per abilitare la scrittura
	EECR |= (1 << EEPE);//Imposto il bit EEPE a 1 per avviare la procedura di scrittura
}
void EEPROM::Write(uint16_t address, uint8_t* pointer, uint16_t n)
{
	for(; n > 0; n--)
	{
		while(EECR & (1 << EEPE));//Attendo che il bit EEPE venga posto a 0 per segnalare che non vi sono procedure in corso sull'EEPROM
		while(SPMCSR & 1);//Attendo che il bit SPMEN venga posto a 0
		
		EEAR = address;//Inserisco l'indirizzo dell'EEPROM del byte corrente da scrivere in EEAR
		EEDR = *pointer;//Inserisco il byte corrente da scrivere in EEDR
		
		EECR |= (1 << EEMPE);//Imposto il bit EEMPE a 1 per abilitare la scrittura
		EECR |= (1 << EEPE);//Imposto il bit EEPE a 1 per avviare la procedura di scrittura
		
		address++;//Avanzo di un byte nell'indirizzo dell'EEPROM
		pointer++;//Avanzo di un byte nell'indirizzo del valore da scrivere
	}
}