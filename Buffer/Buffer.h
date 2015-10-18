#ifndef BUFFER_H
#define BUFFER_H

#include <avr/io.h>

class Buffer
{
	protected:
	uint16_t size;//Dimensione in byte del buffer
	uint8_t* array;//Puntatore alla prima cella di memoria allocata
	uint8_t* firstElement;//Puntatore al primo elemento inserito
	uint8_t* firstSpace;//Puntatore al primo spazio libero
	
	public:
	Buffer();
	Buffer(uint8_t[], uint16_t);
	
	void Init(uint8_t[], uint16_t);//Reinizializza il buffer

	bool IsEmpty();//Verifica che il buffer sia vuoto
	bool IsFull();//Verfica che il buffer sia pieno
	uint16_t Count();//Restituisce il numero di elementi presenti nel buffer
	uint16_t FreeSpace();//Restituisce lo spazio disponibile nel buffer
	
	bool Push(uint8_t);//Inserisce un byte nel buffer
	uint8_t Pull();//Preleva e restituisce il primo byte inserito (FIFO)
	uint8_t Pop();//preleva e restituisce l'ultimo byte inserito (LIFO)
	
	void Flush();//Elimina tutti gli elementi dal buffer
};

#endif