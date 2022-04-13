#pragma once
#include<iostream>
#include"../headers/entity.h"

namespace teleport
{
	void TeleportTo(Vector3* teleportLocation, PlayerEntity* player)
	{//coords are x y z in this order
		player->location.x = teleportLocation->x;
		player->location.y = teleportLocation->y;
		player->location.z = teleportLocation->z;
		std::cout << "\nteleported to saved location [" << teleportLocation->x << ", " << 
			teleportLocation->y << ", " << teleportLocation->z << "]\n";
	}

	void SaveLocation(Vector3* teleportLocation, PlayerEntity* player)
	{//coords are x y z in this order
		teleportLocation->x = player->location.x;
		teleportLocation->y = player->location.y;
		teleportLocation->z = player->location.z;
		std::cout << "\nsaved location [" << teleportLocation->x << ", " <<
			teleportLocation->y << ", " << teleportLocation->z << "]\n";
	}

	void TeleportEntity(Vector3* teleportLocation, PlayerEntity* entity)
	{
		entity->location.x = teleportLocation->x;
		entity->location.y = teleportLocation->y;
		entity->location.z = teleportLocation->z;
		std::cout << "\nentity teleported\n";
	}

	void TeleportAllEntitoes(Vector3* teleportLocation, EntList* entityList)
	{
		for (int i = 1; i <=31; i++)
		{
			entityList->vector[i]->location.x = teleportLocation->x;
			entityList->vector[i]->location.y = teleportLocation->y;
			entityList->vector[i]->location.z = teleportLocation->z;
		}
	}
}

