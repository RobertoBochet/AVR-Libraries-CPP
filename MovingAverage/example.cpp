#include "MovingAverage.h"

int main()
{
	float smaArray[5], wmaArray[5];
	float a = 0;
	
	SMA sma(smaArray, 5);
	WMA wma(wmaArray, 5);
	
	sma.Add(1);
	a = sma.Get();//1
	sma.Add(2);
	a = sma.Get();//1.5
	sma.Add(3);
	sma.Add(4);
	sma.Add(5);
	a = sma.Get();//3
	sma.Add(6);
	a = sma.Get();//4
	
	wma.Add(1);
	a = wma.Get();//1
	wma.Add(2);
	a = wma.Get();//1.67
	wma.Add(3);
	wma.Add(4);
	wma.Add(5);
	a = wma.Get();//3.67
	wma.Add(6);
	a = wma.Get();//4.67
}