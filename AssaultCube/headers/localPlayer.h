#pragma once
#include<Windows.h>
#include<iostream>
#include<cstdint>

/*
*	Here we have the class we got from Re.Class, thank god I came across that program,
*	be careful when u change the value of some stuff since int16_t has a limit of around
*	34.000.
*
*	Vector4 is for worldToScreen but at the moment I don't have any rendering function
*	hooked so there is no need to work on that.
*
*/

struct Vector2 {
	float x, y;
};

struct Vector3 {
	float x, y, z;
};

struct Vector4 {
	float x, y, z, w;
};

// Created with ReClass.NET 1.2 by KN4CK3R

class LocalPlayer
{
public:
	char pad_0000[40]; //0x0000
	Vector3 playerLocation; //0x0028
	float yaw; //0x0034
	float pitch; //0x0038
	char pad_003C[176]; //0x003C
	int16_t health; //0x00EC
	char pad_00EE[26]; //0x00EE
	int16_t pistolMagSize; //0x0108
	char pad_010A[6]; //0x010A
	uint16_t shotgunMagSize; //0x0110
	char pad_0112[2]; //0x0112
	int16_t subMachineGunMagSize; //0x0114
	char pad_0116[2]; //0x0116
	int16_t sniperMagSize; //0x0118
	char pad_011A[2]; //0x011A
	uint16_t N00000215; //0x011C
	char pad_011E[14]; //0x011E
	int16_t pistolAmmo; //0x012C
	char pad_012E[6]; //0x012E
	uint16_t shotgunAmmo; //0x0134
	char pad_0136[2]; //0x0136
	int16_t subMachineGunAmmo; //0x0138
	char pad_013A[2]; //0x013A
	int16_t sniperAmmo; //0x013C
	char pad_013E[2]; //0x013E
	uint16_t rifleAmmo; //0x0140
	char pad_0142[2]; //0x0142
	int16_t grenadeAmmo; //0x0144
	char pad_0146[10]; //0x0146
	int16_t pistolWait; //0x0150
	char pad_0152[6]; //0x0152
	uint16_t shotgunWait; //0x0158
	char pad_015A[2]; //0x015A
	int16_t subMachineGunWait; //0x015C
	char pad_015E[2]; //0x015E
	int16_t sniperWait; //0x0160
	char pad_0162[2]; //0x0162
	uint16_t rifleWait; //0x0164
	char pad_0166[2]; //0x0166
	int16_t grenadeWait; //0x0168
	char pad_016A[10]; //0x016A
	int16_t pistolShotsFired; //0x0174
	char pad_0176[6]; //0x0176
	uint16_t shotgunShotsFired; //0x017C
	char pad_017E[2]; //0x017E
	int16_t subMachineGunShotsFired; //0x0180
	char pad_0182[2]; //0x0182
	int16_t sniperShotsFired; //0x0184
	char pad_0186[2]; //0x0186
	uint16_t rifleShotsFired; //0x0188
	char pad_018A[2]; //0x018A
	int16_t grenadesThrown; //0x018C
	char pad_018E[78]; //0x018E
	int16_t frags; //0x01DC
	char pad_01DE[38]; //0x01DE
	bool forceAttack; //0x0204
	char name[16]; //0x0205
	char pad_0215[567]; //0x0215
}; //Size: 0x044C



void PrintName(LocalPlayer* player)
{
	std::cout << "\nPlayer name -> ";
	for (int i = 0; i < 16; i++)
	{
		std::cout << player->name[i];
	}
	std::cout << '\n';
}


