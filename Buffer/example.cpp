#include "Buffer.h"

int main()
{
	uint8_t bufferArray[32];
	Buffer buffer(bufferArray, 32);
	
	uint8_t a = 0;
	uint16_t b = 0;
	
	buffer.Push(43);
	buffer.Push(32);
	buffer.Push(234);
	buffer.Push(143);
	
	a = buffer.Pop();//143
	a = buffer.Pull();//43
	a = buffer.Pull();//32
	
	b = buffer.Count();//1
	
	buffer.Flush();
	
	b = buffer.Count();//0
	
	buffer.Push(211);
	buffer.Push(64);
	buffer.Push(145);
	buffer.Push(18);
	
	b = buffer.Count();//4
	
	a = buffer.Pull();//211
	a = buffer.Pop();//18
	a = buffer.Pull();//64
	
	b = buffer.Count();//1
}