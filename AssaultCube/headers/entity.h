#pragma once
#include <Windows.h>
#include <iostream>
#include <map>
#include <cstdint>
#include <set>

/*
*	Here we have the class we got from Re.Class, thank god I came across that program,
*	be careful when u change the value of some stuff since int32_t has a limit of around
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

class PlayerEntity
{
public:
	char pad_0000[40]; //0x0000
	Vector3 location; //0x0028
	float yaw; //0x0034
	float pitch; //0x0038
	char pad_003C[12]; //0x003C
	int32_t lowGravity; //0x0048
	char pad_004C[160]; //0x004C
	int32_t health; //0x00EC
	char pad_00F0[24]; //0x00F0
	int32_t pistolMagSize; //0x0108
	int32_t carbineMagSize; //0x010C
	int32_t shotgunMagSize; //0x0110
	int32_t subMachineGunMagSize; //0x0114
	int32_t sniperMagSize; //0x0118
	int32_t rifleMagSize; //0x011C
	char pad_0120[12]; //0x0120
	int32_t pistolAmmo; //0x012C
	int32_t carbineAmmo; //0x0130
	int32_t shotgunAmmo; //0x0134
	int32_t subMachineGunAmmo; //0x0138
	int32_t sniperAmmo; //0x013C
	int32_t rifleAmmo; //0x0140
	int32_t grenadeAmmo; //0x0144
	char pad_0148[8]; //0x0148
	int32_t pistolWait; //0x0150
	int32_t carbineWait; //0x0154
	int32_t shotgunWait; //0x0158
	int32_t subMachineGunWait; //0x015C
	int32_t sniperWait; //0x0160
	int32_t rifleWait; //0x0164
	int32_t grenadeWait; //0x0168
	char pad_016C[8]; //0x016C
	int32_t pistolShotsFired; //0x0174
	int32_t carbineShotsFired; //0x0178
	int32_t shotgunShotsFired; //0x017C
	int32_t subMachineGunShotsFired; //0x0180
	int32_t sniperShotsFired; //0x0184
	int32_t rifleShotsFired; //0x0188
	int32_t grenadeShotsFired; //0x018C
	char pad_0190[116]; //0x0190
	bool forceAttack; //0x0204
	char name[16]; //0x0205
	char pad_0215[1089]; //0x0215
}; //Size: 0x0656

struct EntList
{
	PlayerEntity* vector[32];
};

void PrintName(PlayerEntity* player);

// we return the pointer to the entityList that is the closest to our local player
PlayerEntity* ClosestEntity(PlayerEntity* localPlayer, EntList* entityList);