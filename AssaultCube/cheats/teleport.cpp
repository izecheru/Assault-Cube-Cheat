#include"teleport.h"


void teleport::TeleportTo(Vector3* teleportLocation, PlayerEntity* player)
{//coords are x y z in this order
	player->location.x = teleportLocation->x;
	player->location.y = teleportLocation->y;
	player->location.z = teleportLocation->z;
	std::cout << "\nteleported to saved location [" << teleportLocation->x << ", " <<
		teleportLocation->y << ", " << teleportLocation->z << "]\n";
}

void teleport::SaveLocation(Vector3* teleportLocation, PlayerEntity* player)
{//coords are x y z in this order
	teleportLocation->x = player->location.x;
	teleportLocation->y = player->location.y;
	teleportLocation->z = player->location.z;
	std::cout << "\nsaved location [" << teleportLocation->x << ", " <<
		teleportLocation->y << ", " << teleportLocation->z << "]\n";
}

void teleport::TeleportEntity(Vector3* teleportLocation, PlayerEntity* entity)
{
	entity->location.x = teleportLocation->x;
	entity->location.y = teleportLocation->y;
	entity->location.z = teleportLocation->z;
}

void teleport::TeleportAllEntities(Vector3* teleportLocation, EntList* entityList)
{
	for (int i = 1; i <= 31; i++)
	{
		if (entityList->vector[i] == nullptr)
		{
			continue;
		}
		TeleportEntity(teleportLocation, entityList->vector[i]);
	}
}