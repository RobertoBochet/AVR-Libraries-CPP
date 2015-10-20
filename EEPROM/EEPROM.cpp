#include "EEPROM.h"

template uint8_t EEPROM::Read<uint8_t>(uint16_t);
template uint16_t EEPROM::Read<uint16_t>(uint16_t);
template uint32_t EEPROM::Read<uint32_t>(uint16_t);
template uint64_t EEPROM::Read<uint64_t>(uint16_t);
template int8_t EEPROM::Read<int8_t>(uint16_t);
template int16_t EEPROM::Read<int16_t>(uint16_t);
template int32_t EEPROM::Read<int32_t>(uint16_t);
template int64_t EEPROM::Read<int64_t>(uint16_t);
template float EEPROM::Read<float>(uint16_t);
template double EEPROM::Read<double>(uint16_t);

template void EEPROM::Read<uint8_t>(uint16_t, uint8_t[], uint16_t);
template void EEPROM::Read<uint16_t>(uint16_t, uint16_t[], uint16_t);
template void EEPROM::Read<uint32_t>(uint16_t, uint32_t[], uint16_t);
template void EEPROM::Read<uint64_t>(uint16_t, uint64_t[], uint16_t);
template void EEPROM::Read<int8_t>(uint16_t, int8_t[], uint16_t);
template void EEPROM::Read<int16_t>(uint16_t, int16_t[], uint16_t);
template void EEPROM::Read<int32_t>(uint16_t, int32_t[], uint16_t);
template void EEPROM::Read<int64_t>(uint16_t, int64_t[], uint16_t);
template void EEPROM::Read<float>(uint16_t, float[], uint16_t);
template void EEPROM::Read<double>(uint16_t, double[], uint16_t);

template void EEPROM::Write<uint8_t>(uint16_t, uint8_t);
template void EEPROM::Write<uint16_t>(uint16_t, uint16_t);
template void EEPROM::Write<uint32_t>(uint16_t, uint32_t);
template void EEPROM::Write<uint64_t>(uint16_t, uint64_t);
template void EEPROM::Write<int8_t>(uint16_t, int8_t);
template void EEPROM::Write<int16_t>(uint16_t, int16_t);
template void EEPROM::Write<int32_t>(uint16_t, int32_t);
template void EEPROM::Write<int64_t>(uint16_t, int64_t);
template void EEPROM::Write<float>(uint16_t, float);
template void EEPROM::Write<double>(uint16_t, double);

template void EEPROM::Write<uint8_t>(uint16_t, uint8_t[], uint16_t);
template void EEPROM::Write<uint16_t>(uint16_t, uint16_t[], uint16_t);
template void EEPROM::Write<uint32_t>(uint16_t, uint32_t[], uint16_t);
template void EEPROM::Write<uint64_t>(uint16_t, uint64_t[], uint16_t);
template void EEPROM::Write<int8_t>(uint16_t, int8_t[], uint16_t);
template void EEPROM::Write<int16_t>(uint16_t, int16_t[], uint16_t);
template void EEPROM::Write<int32_t>(uint16_t, int32_t[], uint16_t);
template void EEPROM::Write<int64_t>(uint16_t, int64_t[], uint16_t);
template void EEPROM::Write<float>(uint16_t, float[], uint16_t);
template void EEPROM::Write<double>(uint16_t, double[], uint16_t);

template <typename T> T EEPROM::Read(uint16_t address)
{
	T value = 0;//Alloco e inizializzo la variabile da restituire a 0
	uint8_t* pointer;//Alloco un puntatore di un byte che puntera al byte corrente da leggere
	pointer = (uint8_t*) &value;//Attribuisco al puntatore l'indirizzo del low byte di value
	for(uint8_t i = sizeof(T);i > 0;i--)//Eseguo un for che si ripete per il numero di byte del valore da leggere
	{
		while(EECR & (1 << EEPE));//Attendo che il bit EEPE venga posto a 0 per segnalare che non vi sono procedure in corso sull'EEPROM
		while(SPMCSR & 1);//Attendo che il bit SPMEN venga posto a 0
		
		EEAR = address;//Inserisco l'indirizzo del dato da recuperare in EEAR
		
		EECR |= (1 << EERE);//Imposto il bit EERE a 1 per avviare la procedura di lettura
		
		*pointer = EEDR;//Attribuisco al byte corrente il valore letto
			
		address++;//Avanzo di un byte nell'indirizzo dell'EEPROM
		pointer++;//Avanzo di un byte nell'indirizzo del valore da leggere
	}
	return value;//Restituisco il valore estratto dall'EEPROM
}
template <typename T> void EEPROM::Read(uint16_t address, T array[], uint16_t n)
{
	uint8_t* pointer;//Alloco un puntatore di un byte che puntera al byte corrente da leggere
	if(n != 0)//Verifico che l'array non abbia lunghezza nulla
	{
		pointer = (uint8_t*) array;//Attribuisco al puntatore l'indirizzo del low byte del primo elemento di array
		n *= sizeof(T);//Moltiplico il numero di elementi da leggere per il numero di byte per ogni singolo elemento per ottenere il numero totale di byte da leggere
		for(;n>0;n--)//Eseguo un for che si ripete per il numero di byte da leggere
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
}

template <typename T> void EEPROM::Write(uint16_t address, T value)
{
	uint8_t* pointer;//Alloco un puntatore di un byte che puntera al byte corrente da scrivere
	pointer = (uint8_t*) &value;//Attribuisco al puntatore l'indirizzo del low byte di value
	for(uint8_t i = sizeof(T);i > 0;i--)//Eseguo un for che si ripete per il numero di byte del valore da scrivere
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
template <typename T> void EEPROM::Write(uint16_t address, T array[], uint16_t n)
{
	uint8_t* pointer;//Alloco un puntatore di un byte che puntera al byte corrente da scrivere
	if(n != 0)//Verifico che l'array non abbia lunghezza nulla
	{
		pointer = (uint8_t*) &array;//Attribuisco al puntatore l'indirizzo del low byte del primo elemento di array
		n *= sizeof(T);//Moltiplico il numero di elementi da scrivere per il numero di byte per ogni singolo elemento per ottenere il numero totale di byte da scrivere
		for(;n>0;n--)
		{
			while(EECR & (1 << EEPE));//Attendo che il bit EEPE venga posto a 0 per segnalare che non vi sono procedure in corso sull'EEPROM
			while(SPMCSR & 1);//Attendo che il bit SPMEN venga posto a 0
			
			EEAR = address;//Inserisco l'indirizzo del dato da scrivere in EEAR
			EEDR = *pointer;//Inserisco il dato da scrivere in EEDR
			
			EECR |= (1 << EEMPE);//Imposto il bit EEMPE a 1 per abilitare la scrittura
			EECR |= (1 << EEPE);//Imposto il bit EEPE a 1 per avviare la procedura di scrittura
			
			address++;//Avanzo di un byte nell'indirizzo dell'EEPROM
			pointer++;//Avanzo di un byte nell'indirizzo del valore da scrivere
		}
	}
}