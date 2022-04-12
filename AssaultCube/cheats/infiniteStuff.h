#pragma once
#include<iostream>
#include"../headers/localPlayer.h"

void Health(LocalPlayer* player, bool enable)
{
	if (enable)
	{
		// 34.000 cause I set the data type as int16_t
		player->health = 34000;
	}
}

void Ammo(LocalPlayer* player, bool enable)
{
	if (enable)
	{
		player->sniperAmmo = 20;
		player->pistolAmmo = 20;
		player->rifleAmmo = 20;
		player->subMachineGunAmmo = 20;
		player->shotgunAmmo = 20;
		player->grenadeAmmo = 20;
	}
}