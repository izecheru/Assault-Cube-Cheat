#pragma once
#include<iostream>

void Health(bool enabled, int* healthPtr, int ammount)
{
	if (enabled)
	{
		*(healthPtr) = ammount;
	}
}

void Ammo(bool enabled, int* ammoPtr, int ammount = 20)
{
	if (enabled)
	{
		*ammoPtr = ammount;
	}
}