#include "MovingAverage.h"

SMA::SMA(float array[], uint32_t size)
{
	this->oldestElement = this->beginningArray = array;//Imposto i puntatori all'inizio dell'array e all'elemento meno recente con l'inizio dell'array fornito
	this->endArray = array + size - 1;//Imposto il puntatore alla fine dell'array attraverso l'inizio dell'array fornito
	this->elements = this->sum = 0;//Imposto a 0 il numero di elementi della media e la somma degli stessi
}
void SMA::Add(float value)
{
	if(this->beginningArray + this->elements - 1 == this->endArray) this->sum -= *this->oldestElement;//Se l'array è pieno sotraggo alla somma il valore meno recente prima di rimuoverlo
	else this->elements++;//In caso contrario incremento di uno gli elementi che compongono la media
	
	*this->oldestElement = value;//Aggiorno il valore meno recente con il nuovo valore
	this->sum += value;//Aggiungo il nuovo valore alla somma
	
	if(this->oldestElement == this->endArray) this->oldestElement = this->beginningArray;//Se l'elemento aggiornato era l'ultimo dell'array fisico porto il puntatore all'elemento meno recente all'inizio dell'array
	else this->oldestElement++;//In caso contrario porto il puntatore all'elemento meno recente al successivo elemento
}
double SMA::Get()
{
	return this->sum / this->elements;//Restituisco la media semplice
}
void SMA::Clear()
{
	this->oldestElement = this->beginningArray;//Reimposto il puntatore al valore meno recente al primo elemento dell'array
	this->elements = this->sum = 0;//Reimposto a 0 il numero degli elementi della media e la somma degli stessi
}