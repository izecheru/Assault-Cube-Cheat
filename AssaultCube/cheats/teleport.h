#pragma once
#include<iostream>
#include"../headers/localPlayer.h"
namespace teleport
{
	void TeleportTo(Vector3* teleportLocation, LocalPlayer* player)
	{//coords are x y z in this order
		player->playerLocation.x = teleportLocation->x;
		player->playerLocation.y = teleportLocation->y;
		player->playerLocation.z = teleportLocation->z;
		std::cout << "\nteleported to saved location [" << teleportLocation->x << ", " << 
			teleportLocation->y << ", " << teleportLocation->z << "]\n";
	}

	void SaveLocation(Vector3* teleportLocation, LocalPlayer* player)
	{//coords are x y z in this order
		teleportLocation->x = player->playerLocation.x;
		teleportLocation->y = player->playerLocation.y;
		teleportLocation->z = player->playerLocation.z;
		std::cout << "\nsaved location [" << teleportLocation->x << ", " <<
			teleportLocation->y << ", " << teleportLocation->z << "]\n";
	}
}

