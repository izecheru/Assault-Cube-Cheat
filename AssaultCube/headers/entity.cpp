#pragma once
#include"entity.h"

void PrintName(PlayerEntity* player)
{
	std::cout << " Entity name -> ";
	for (int i = 0; i < 16; i++)
	{
		std::cout << player->name[i];
	}
	std::cout << '\n';
}

// we return the pointer to the entityList that is the closest to our local player
PlayerEntity* ClosestEntity(PlayerEntity* localPlayer, EntList* entityList)
{
	// first pair parameter is float cause we want the closest one and
	// since map is by default sorted by keyes, we pass the distance as key
	std::map<float, PlayerEntity*> distance;
	for (int i = 1; i < 32; i++)
	{
		float _x = localPlayer->location.x - entityList->vector[i]->location.x;
		float _y = localPlayer->location.y - entityList->vector[i]->location.y;
		distance.insert(std::pair(sqrtf(_x * _x + _y * _y), entityList->vector[i]));
	}
	return distance.begin()->second;
}