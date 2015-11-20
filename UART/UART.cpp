#include "UART.h"
#include <avr/interrupt.h>
#include "../Buffer/Buffer.h"

namespace UART
{
	Buffer RxBuffer;//Buffer di ricezione
	Buffer TxBuffer;//Buffer di trasmissione
	
	inline void RxInterruptEnabled();//Abilita l'interrupt per la ricezione di un byte
	inline void RxInterruptDisabled();//Disabilita l'interrupt per la ricezione di un byte
	inline void TxInterruptEnabled();//Abilita l'interrupt per la conclusione di invio di un byte
	inline void TxInterruptDisabled();//Disabilita l'interrupt per la conclusione di invio di un byte
	
	inline void ReceiveData();//Inizia la ricezione di un byte
	inline void SendData();//Inizia la trasmissione di un byte
}

void UART::Init(uint16_t ubrr, uint8_t rxBufferArray[], uint8_t rxBufferArraySize, uint8_t txBufferArray[], uint8_t txBufferArraySize)
{
	UCSR0B = (1<<RXEN0) | (1<<TXEN0); //Abilito il pin di ricezione e il pin di trasmissione
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);//Imposto a 8 la lunghezza in bit di un carattere
	
	UART::SetUBRR(ubrr);
	
	UART::RxBuffer.Init(rxBufferArray, rxBufferArraySize);//Inizializzo il buffer di ricezione
	UART::TxBuffer.Init(txBufferArray, txBufferArraySize);//Inizializzo il buffer di trasmissione
		
	UART::RxInterruptEnabled();//Abilito l'interrupt per la ricezione di un byte
	UART::TxInterruptEnabled();//Abilito l'interrupt per la conclusione di invio di un byte
	
	sei();//Abilito gli interrupt globali
}

void UART::SetUBRR(uint16_t ubrr)
{
	UBRR0H = ubrr >> 8;
	UBRR0L = ubrr;
}

void UART::DoubleSpeedEnabled()
{
	UCSR0A |= 1 << U2X0;
}
void UART::DoubleSpeedDisabled()
{
	UCSR0A &= ~(1 << U2X0);
}

inline void UART::RxInterruptEnabled()
{
	UCSR0B |= 1 << RXCIE0;
}
inline void UART::RxInterruptDisabled()
{
	UCSR0B &= ~(1 << RXCIE0);
}
inline void UART::TxInterruptEnabled()
{
	UCSR0B |= 1 << TXCIE0;
}
inline void UART::TxInterruptDisabled()
{
	UCSR0B &= ~(1 << TXCIE0);
}

uint8_t UART::RxAvailable()
{
	return UART::RxBuffer.Count();//Restituisco il numero di byte presenti nel buffer di ricezione
}

uint8_t UART::Rx()
{
	return UART::RxBuffer.Pull();//Prelevo e restituisco il byte ricevuto meno recente
}
void UART::Rx(uint8_t array[], uint16_t n)
{
	for(; n != 0; n--)//Eseguo il ciclo per il numero di byte da copiare
	{
		*array = UART::RxBuffer.Pull();//Prelevo e inserisco il byte ricevuto meno recente nell'array 
		array++;//Sposto il puntatore all'array avanti di un byte
	}
}

void UART::Tx(uint8_t value)
{
	while(UART::TxBuffer.FreeSpace() == 0);//Attendo che nel buffer di trasmisione vi sia almeno un byte libero
	
	UART::TxInterruptDisabled();//Disabilito l'interrupt per la conclusione di invio di un byte
	
	UART::TxBuffer.Push(value);//Inserisco il byte nel buffer di trasmissione
	
	UART::TxInterruptEnabled();//Abilito l'interrupt per la conclusione di invio di un byte
	
	UART::SendData();//Rinizio la procedura di invio dei dati nel buffer
}
void UART::Tx(const char* s)
{
	do {
		while(!UART::TxBuffer.IsEmpty());//Attendo che il buffer sia completamente vuoto
		
		UART::TxInterruptDisabled();//Disabilito l'interrupt per la conclusione di invio di un byte
		
		do {
			UART::TxBuffer.Push(*s);//Inserisco il carattere corrente nel buffer di trasmissione
			s++;//Faccio avanzare di un carattere il puntatore al carattere corrente
		} while(*s != '\0' && !UART::TxBuffer.IsFull());//Continuo fintanto che il carattere corrente è il carattere '\0' di fine stringa o il buffer di trasmissione sia pieno
		
		UART::TxInterruptEnabled();//Abilito l'interrupt per la conclusione di invio di un byte
		
		UART::SendData();//Rinizio la procedura di invio dei dati
	} while(*s != '\0');//Rieseguo il ciclo se non è stato ancora incontrato il carattere '\0' di fine stringa
}
void UART::Tx(const uint8_t array[], uint16_t n)
{
	do {
		while(UART::TxBuffer.FreeSpace() < n && !UART::TxBuffer.IsEmpty());//Attendo che nel buffer vi sia spazio sufficiente per tutti i byte o che sia completamente vuoto
		
		UART::TxInterruptDisabled();//Disabilito l'interrupt per la conclusione di invio di un byte
		
		do {
			UART::TxBuffer.Push(*array);//Inserisco il byte corrente nel buffer di trasmissione
			n--;//Diminuisco di uno i byte da dover ancora inviare
			array++;//Sposto di un byte in avanti il puntatore al byte corrente
		} while(n != 0 && !UART::TxBuffer.IsFull());//Continuo fintanto che i byte ancora da inviare siano finiti o il buffer di trasmissione sia pieno
		
		UART::TxInterruptEnabled();//Abilito l'interrupt per la conclusione di invio di un byte
		
		UART::SendData();//Rinizio la procedura di invio dei dati
	} while(n != 0);//Rieseguo il ciclo se rimangono ancora byte da inviare
}

inline void UART::ReceiveData()
{
	uint8_t waste;//Alloco un byte in caso dovessi eliminare dei dati
	if(UART::RxBuffer.IsFull()) waste = UDR0;//Se il Buffer di ricezione è pieno scarto il valore ricevuto
	else UART::RxBuffer.Push(UDR0);//In caso contrario inserisco il byte ricevuto nel buffer di ricezione
}
inline void UART::SendData()
{
	if(!UART::TxBuffer.IsEmpty())//Verifico che il buffer di trasmissione non sia vuoto
	{
		while(!(UCSR0A & (1 << UDRE0)));//Attendo che il modulo sia pronto
		UDR0 = UART::TxBuffer.Pull();//Prelevo dal buffer di trasmissione ed invio un byte
	}
}

ISR(USART_RX_vect) { UART::ReceiveData(); }//Al verificarsi dell'interrupt che segnala la fine della ricezione di un byte inizio la ricezione software dello stesso
ISR(USART_TX_vect) { UART::SendData(); }//Al verificarsi dell'interrupt che segnala la fine della trasmissione di un byte inizio la procedura per inviare un altro byte