#pragma once

#include <avr/io.h>

namespace TimeLife
{
	void Setup(uint32_t);//(timerFrequency)//Inizializza la funzione Millis accetando come paramentro {timerFrequency} la frequenza del timer
	void Reset();//Resetta i contatori della Millis
	
	uint64_t Millis();//Restituisce i millisecondi passati nell'inizializzazione di Millis
}