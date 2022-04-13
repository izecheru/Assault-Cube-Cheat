#pragma once
#include<iostream>
#include "../headers/entity.h"

namespace stop
{
	// should be called in main loop since it should set coordinates each time to
	// those that were when function got enabled
	void Move(EntList* entList, bool enabled)
	{
		if (enabled)
		{
			for (int i = 1; i <= 31; i++)
			{
				entList->vector[i]->location.x = entList->vector[i]->location.x;
				entList->vector[i]->location.y = entList->vector[i]->location.y;
				entList->vector[i]->location.z = entList->vector[i]->location.z;
			}
		}
	}
}