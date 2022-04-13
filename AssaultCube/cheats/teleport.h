#pragma once
#include<iostream>
#include"../headers/entity.h"

namespace teleport
{
	void TeleportTo(Vector3* teleportLocation, PlayerEntity* player);

	void SaveLocation(Vector3* teleportLocation, PlayerEntity* player);

	void TeleportEntity(Vector3* teleportLocation, PlayerEntity* entity);

	void TeleportAllEntitoes(Vector3* teleportLocation, EntList* entityList);
}

