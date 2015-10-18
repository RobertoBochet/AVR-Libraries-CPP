#include "Buffer.h"
#include <stdlib.h>

Buffer::Buffer() {}
Buffer::Buffer(uint8_t array[], uint16_t size)
{	
	this->Init(array, size);
}

void Buffer::Init(uint8_t array[], uint16_t size)
{
	this->size = size;//Imposto la variabile che indica le dimensioni del buffer
	this->array = this->firstSpace = array;//Imposto il puntatore all'array e al primo spazio libero
	this->firstElement = NULL;//Imposto il puntatore al primo elemento a NULL
}

bool Buffer::IsEmpty()
{
	return this->firstElement == NULL;//Se il puntatore al primo elemento punta a NULL segno che il buffer è vuoto restituisco true
}
bool Buffer::IsFull()
{
	return this->firstElement == this->firstSpace;//Se i puntatori del primo elemento e primo spazio libero puntano alla stessa cella segno che il buffer è pieno restituisco true
}
uint16_t Buffer::Count()
{
	if(this->IsEmpty()) return 0;//Se il buffer è vuoto restituisco 0
	if(this->IsFull()) return this->size;//Se il buffer è pieno restituisco la dimensione del buffer
	
	if(this->firstElement < this->firstSpace) return this->firstSpace - this->firstElement;//Se il puntatore al primo elemento si trova prima del primo spazio libero restituisco la differenza tra i due
	else return this->size - (this->firstElement - this->firstSpace);//Se il puntatore al primo elemento di trova dopo il primo spazio libero restituisco la dimensione del buffer meno la differenza tra il puntatore al primo elemento e il primo spazio libero
}
uint16_t Buffer::FreeSpace()
{
	return this->size - this->Count();//Restituisco il complemento di Count
}

bool Buffer::Push(uint8_t value)
{
	if (this->IsFull()) return false;//Se il buffer è pieno restituisco false
	
	if (this->IsEmpty()) this->firstElement = this->firstSpace;//Se il buffer è vuoto imposto il puntatore al primo elemento al primo spazio libero
	*this->firstSpace = value;//Imposto il valore nel primo spazio disponibile nel buffer
	this->firstSpace++;//Sposto il puntatore una cella in avanti
	if (this->array + this->size == this->firstSpace) this->firstSpace = this->array;//Se il puntatore sconfina in una zona al di fuori del buffer lo si reimposta alla prima cella allocata
	
	return true;//Restituisco true se il valore è stato inserito correttamente
}
uint8_t Buffer::Pull()
{
	uint8_t value;
	if (this->IsEmpty()) return 0;//Se il buffer è vuoto restituisco 0
	
	value = *this->firstElement;//Copio il valore nella variabile che verrà restituita
	this->firstElement++;//Sposto il puntatore una cella in avanti
	if (this->array + this->size == this->firstElement) this->firstElement = this->array;//Se il puntatore sconfina in una zona al di fuori del buffer lo si reimposta alla prima cella allocata
	if (this->firstElement == this->firstSpace) this->firstElement = NULL;//Se i due puntatori finisco a puntare alla stessa cella come se il buffer fosse pieno reimposto il puntatore al primo elemento a null
	
	return value;//Restituisco il valore
}
uint8_t Buffer::Pop()
{
	if (this->IsEmpty()) return 0;//Se il buffer è vuoto restituisco 0
	
	if (this->firstSpace == this->array) this->firstSpace += this->size - 1;//Se il puntatore al primo spazio libero punta alla prima cella allocata allora lo sposto all'ultima cella allocata
	else this->firstSpace--;//In caso contrario sposto il puntatore al primo spazio libero indietro di una cella
	if (this->firstElement == this->firstSpace) this->firstElement = NULL;//Se i due puntatori finisco a puntare alla stessa cella come se il buffer fosse pieno reimposto il puntatore al primo elemento a null
	
	return *this->firstSpace;//Restituisco il valore
}

void Buffer::Flush()
{
	this->firstElement = NULL;//Reimposto il puntatore al primo elemento a NULL
	this->firstSpace = this->array;//Reimposto il puntatore al primo spazio libero al primo elemento dell'array
}