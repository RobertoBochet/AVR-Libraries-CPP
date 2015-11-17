#pragma once

#include <avr/io.h>

namespace UART
{
	void Init(uint16_t, uint8_t[], uint8_t, uint8_t[], uint8_t);//(UBRR, RxBufferArray, RxBufferArraySize, TxBufferArray, TxBufferArraySize)//Inizializza il modulo UART con UBRR {UBRR}, buffer di ricezione {RxBufferArray} di {RxBufferArraySize} elementi e buffer di trasmissione {TxBufferArray} di {TxBufferArraySize} elementi
	
	void SetUBRR(uint16_t);//(UBRR)//Imposta l'ubrr a {UBRR}
	
	void DoubleSpeedEnabled();//Abilita la velocità doppia
	void DoubleSpeedDisabled();//Disabilità la velocità doppia
	
	uint8_t RxAvailable();//Restituisce il numero di elementi nel buffer di ricezione

	uint8_t Rx();//Preleva dal buffer di ricezione e restituisce il byte meno recente
	void Rx(uint8_t[], uint16_t);//(array, n)//Preleva {n} elementi dal buffer di ricezione e li posiziona in {array}

	void Tx(uint8_t);//(value)//Trasmette il byte {value}
	void Tx(char*);//(char)//Trasmette una stringa a partire dal carattere {char}
	void Tx(uint8_t[], uint16_t);//(array, n)//Trasmette {n} byte dell'array {array}
}