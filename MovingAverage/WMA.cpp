#include "MovingAverage.h"

WMA::WMA(float array[], uint32_t size)
{
	this->oldestElement = this->beginningArray = array;//Imposto i puntatori all'inizio dell'array e all'elemento meno recente con l'inizio dell'array fornito
	this->endArray = array + size - 1;//Imposto il puntatore alla fine dell'array attraverso l'inizio dell'array fornito
	this->elements = 0;//Imposto a 0 il numero di elementi della media
}
void WMA::Add(float value)
{
	if(this->beginningArray + this->elements - 1 != this->endArray) this->elements++;//Se l'array non è pieno incremento di uno gli elementi che compongono la media
	
	*this->oldestElement = value;//Aggiorno il valore meno recente con il nuovo valore
	
	if(this->oldestElement == this->endArray) this->oldestElement = this->beginningArray;//Se l'elemento aggiornato era l'ultimo dell'array fisico porto il puntatore all'elemento meno recente all'inizio dell'array
	else this->oldestElement++;//In caso contrario porto il puntatore all'elemento meno recente al successivo elemento
}
float WMA::Get()
{
	float* currentElement;//Crreo un puntatore per il valore corrente della somma
	double sum = 0;//Creo una variabile per la somma ponderata e la imposto a 0
	uint64_t divisor = 0;//Creo una variabile per il divisore della somma e la imposto a 0
	
	currentElement = (this->beginningArray + this->elements - 1 == this->endArray) ? this->oldestElement : this->beginningArray;//Imposto il puntatore all'elemento corrente con l'elemento meno recente
	
	for(uint32_t elements = 1; elements - 1 != this->elements; elements++)//Creo un ciclo per ogni elemento della media
	{
		sum += (double) *currentElement * elements;//Aggiungo alla somma il valore corrente moltiplicato per la sua rilevanza nella media
		divisor += elements;//Aggiorno il valore del divisore sommandoci il numero di rilevanza del valore corrente 
		
		if(currentElement == this->endArray) currentElement = this->beginningArray;//Se l'elemento corrente è l'ultimo dell'array fisico porto il puntatore all'elemento corrente all'inizio dell'array
		else currentElement++;//In caso contrario porto il puntatore all'elemento corrente al successivo elemento
	}
	return sum / divisor;//Restituisco la media ponderata
}
void WMA::Clear()
{
	this->oldestElement = this->beginningArray;//reimposto il valore piu vecchio al primo elemento dell'array
	this->elements = 0;//Reimposto a 0 il numero degli elementi della media e la somma degli stessi
}