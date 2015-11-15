#include "UART.h"
#include <avr/interrupt.h>
#include "../Buffer/Buffer.h"

namespace UART
{
	Buffer RxBuffer;
	Buffer TxBuffer;
	
	void RxInterruptEnabled();//Abilita l'interrupt per la ricezione di un byte
	void RxInterruptDisabled();//Disabilita l'interrupt per la ricezione di un byte
	void TxInterruptEnabled();//Abilita l'interrupt per la conclusione di invio di un byte
	void TxInterruptDisabled();//Disabilita l'interrupt per la conclusione di invio di un byte
	
	void ReceiveData();//Inizia la ricezione di un byte
	void SendData();//Inizia la trasmissione di un byte
}

void UART::Init(uint16_t ubrr, uint8_t rxBufferArray[], uint8_t rxBufferArraySize, uint8_t txBufferArray[], uint8_t txBufferArraySize)
{
	UCSR0B = (1<<RXEN0) | (1<<TXEN0); //Abilito il pin di ricezione e il pin di trasmissione
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);//Imposto a 8 la lunghezza in bit di un carattere
	
	UBRR0H = ubrr >> 8;
	UBRR0L = ubrr;
	
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

void UART::RxInterruptEnabled()
{
	UCSR0B |= 1 << RXCIE0;
}
void UART::RxInterruptDisabled()
{
	UCSR0B &= ~(1 << RXCIE0);
}
void UART::TxInterruptEnabled()
{
	UCSR0B |= 1 << TXCIE0;
}
void UART::TxInterruptDisabled()
{
	UCSR0B &= ~(1 << TXCIE0);
}

uint8_t UART::RxAvailable()
{
	return RxBuffer.Count();//Restituisco il numero di byte presenti nel buffer di ricezione
}

uint8_t UART::Rx()
{
	return RxBuffer.Pull();//Prelevo e restituisco il byte ricevuto meno recente
}
void UART::Rx(uint8_t array[], uint16_t n)
{
	for(; n != 0; n--)//Eseguo il ciclo per il numero di byte da copiare
	{
		*array = RxBuffer.Pull();
		array++;//Sposto il puntatore all'array avanti di un byte
	}
}

void UART::Tx(uint8_t data)
{
	UART::TxInterruptDisabled();//Disabilito l'interrupt per la conclusione di invio di un byte
	
	TxBuffer.Push(data);//Inserisco il byte nel buffer di trasmissione
	
	UART::TxInterruptEnabled();//Abilito l'interrupt per la conclusione di invio di un byte
	
	UART::SendData();//Rinizio la procedura di invio dei dati nel buffer
}
void UART::Tx(char* s)
{
	UART::TxInterruptDisabled();//Disabilito l'interrupt per la conclusione di invio di un byte
	
	while(*s != '\0')//Eseguo il ciclo fintanto che il carattere corrente non è '\0' (fine stringa)
	{
		TxBuffer.Push(*s);//Invio il carattere corrente
		s++;//Sposto il puntatore al carattere corrente a quello successivo
	}
	
	UART::TxInterruptEnabled();//Abilito l'interrupt per la conclusione di invio di un byte

	UART::SendData();//Rinizio la procedura di invio dei dati nel buffer
}
void UART::Tx(uint8_t array[], uint16_t n)
{
	if(TxBuffer.FreeSpace() < n)//In caso nel buffer di trasmissione non vi sia spazio sufficiente per trasmettere tutto l'array in una volta sola
	{
		for(; n != 0; n--)//Eseguo il ciclo per il numero di byte da copiare
		{
			UART::Tx(*array);
			array++;//Sposto il puntatore all'array avanti di un byte
		}
	}
	else//Se invece nel buffer di trasmissione vi è spazio sufficiente per trasmettere tutto l'array in una volta sola
	{
		UART::TxInterruptDisabled();//Disabilito l'interrupt per la conclusione di invio di un byte
		
		for(; n != 0; n--)//Eseguo il ciclo per il numero di byte da copiare
		{
			TxBuffer.Push(*array);
			array++;//Sposto il puntatore all'array avanti di un byte
		}
		
		UART::TxInterruptEnabled();//Abilito l'interrupt per la conclusione di invio di un byte

		UART::SendData();//Rinizio la procedura di invio dei dati nel buffer
	}
}

void UART::ReceiveData()
{
	uint8_t waste;//Alloco un byte in caso dovessi eliminare dei dati
	if(RxBuffer.IsFull()) waste = UDR0;//Se il Buffer di ricezione è pieno scarto il valore ricevuto
	else RxBuffer.Push(UDR0);//In caso contrario inserisco il byte ricevuto nel buffer di ricezione
}
void UART::SendData()
{
	if(!TxBuffer.IsEmpty())//Verifico che il buffer di trasmissione non sia vuoto
	{
		while(!(UCSR0A & (1 << UDRE0)));//Attendo che il modulo sia pronto
		UDR0 = TxBuffer.Pull();//Prelevo dal buffer di trasmissione ed invio un byte
	}
}

ISR(USART_RX_vect) { UART::ReceiveData(); }//Al verificarsi dell'interrupt che segnala la fine della ricezione di un byte inizio la ricezione software dello stesso
ISR(USART_TX_vect) { UART::SendData(); }//Al verificarsi dell'interrupt che segnala la fine della trasmissione di un byte inizio la procedura per inviare un altro byte