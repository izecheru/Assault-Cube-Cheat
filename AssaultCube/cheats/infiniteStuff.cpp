#include"infiniteStuff.h"

void Health(PlayerEntity* player, bool enable)
{
	if (enable)
	{
		// 34.000 cause I set the data type as int16_t
		player->health = 1337;
	}
}

void Ammo(PlayerEntity* player, bool enable)
{
	if (enable)
	{
		player->sniperAmmo = 1337;
		player->pistolAmmo = 1337;
		player->rifleAmmo = 1337;
		player->subMachineGunAmmo = 1337;
		player->shotgunAmmo = 1337;
		player->grenadeAmmo = 1337;
		player->carbineAmmo = 1337;
	}
}