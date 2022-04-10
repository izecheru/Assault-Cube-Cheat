#pragma once
#include<iostream>
#include"offsets.h"


void PrintEntityName(int* entityPtr)
{
	for (int i = 0; i < 16; i++)
	{
		// since char is 1 byte we get the first character adress and then
		// we add 1 to get the next character, max len is 16
		std::cout << *(char*)(*entityPtr + offsets::ac_name + i);
		//might add some random string generator later on
		//would be cool to see the name changing constantly
	}
}

void EntityListHealth(int* entityListPtr)
{
	std::cout << '\n';
	for (int i = 4; i < (31 * 4); i += 4)
	{
		//what the fuck is this shit?
		PrintEntityName((int*)(*entityListPtr + i));
		if (*(int*)(*(int*)(*entityListPtr + i) + offsets::ac_health) == 0)
		{
			continue;
		}
		std::cout << '\t' << *(int*)(*(int*)(*entityListPtr + i) + offsets::ac_health) << '\n';
	}
}

void TeleportEntityTo(float* teleportLocation, int* entityListPtr)
{
	std::cout << "teleporting all the bitches to [" << teleportLocation[0] << ", " << teleportLocation[1] << ", " << teleportLocation[2] << '\n';
	for (int i = 4; i < (31 * 4); i += 4)
	{
		*(int*)(*(int*)(*entityListPtr + i) + offsets::ac_x) = teleportLocation[0];
		*(int*)(*(int*)(*entityListPtr + i) + offsets::ac_y) = teleportLocation[1];
		*(int*)(*(int*)(*entityListPtr + i) + offsets::ac_z) = teleportLocation[2];
	}
}