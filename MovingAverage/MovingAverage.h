#pragma once

#include <avr/io.h>

class SMA//Media mobile semplice
{
	protected:
	float* beginningArray;//Puntatore al primo elemento dell'array
	float* endArray;//Puntatore all'ultimo elemento dell'array
	float* oldestElement;//Puntatore all'elemento meno recente dell'array
	uint32_t elements;//Numero di elementi della media
	double sum;//Sommatoria degli elementi della media
	
	public:
	SMA(float[], uint32_t);//(array, size)//Inizializza la media mobile semplice con {array} di {size} elementi
	void Add(float);//(value)//Aggiunge come nuovo valore {value} alla media
	double Get();//Restituisce la media
	void Clear();//Resetta la media
};

class WMA//Media mobile ponderata
{
	protected:
	float* beginningArray;//Puntatore al primo elemento dell'array
	float* endArray;//Puntatore all'ultimo elemento dell'array
	float* oldestElement;//Puntatore all'elemento meno recente dell'array
	uint32_t elements;//Numero di elementi della media
	
	public:
	WMA(float[], uint32_t);//(array, size)//Inizializza la media mobile ponderata con {array} di {size} elementi
	void Add(float);//(value)//Aggiunge come nuovo valore {value} alla media
	double Get();//Restituisce la media
	void Clear();//Resetta la media
};