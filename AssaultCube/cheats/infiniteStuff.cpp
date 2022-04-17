#include"infiniteStuff.h"
#include"../headers/hooks.h"

void Health(PlayerEntity* player, bool enable)
{
	if (enable)
	{
		player->health = 1337;
	}
}

void Ammo(PlayerEntity* player, bool enable)
{
	if (enable)
	{
		player->carbineAmmo = 1337;
		player->shotgunAmmo = 1337;
		player->pistolAmmo = 1337;
		player->sniperAmmo = 1337;
		player->grenadeAmmo = 1337;
		player->rifleAmmo = 1337;
		player->subMachineGunAmmo = 1337;
	}
}