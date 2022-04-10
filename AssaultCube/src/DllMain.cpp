#include<Windows.h>
#include<iostream>
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<thread>

#include "../headers/entities.h"
#include "../cheats/infiniteStuff.h"
#include "../cheats/teleport.h"
#include "../headers/hooks.h"

#pragma comment(lib, "Winmm.lib")

#define UINJECT "E:/repository/repo/audio/uninject.wav"
#define INJECT "E:/repository/repo/audio/inject.wav"

/*
----------------FEATURE IDEAS-----------------

----------------FEATURE IDEAS-----------------
*/

/*
SOME STUFF ABOUT OFFSETS
---coords---
x - 0x0004
y - 0x0008
z - 0x000C
------------
health - 0x00EC
ammo - 0x140
frags - 0x01DC
localPlayer - 0x17B264 0x187C0C 0x17B370
entityList - 0x187c10
name - 0x205
note to me -> mov, [eax+esi*4] 
[] means dereferencing pointer
eax+esi*4 would be some array stuff
4 size of one instance in array, esi the index
00548A94
*/



void PrintName(int* localPlayer)
{
	char* name;
	for (int i = 0; i < 16; i++)
	{
		// since char is 1 byte we get the first character adress and then
		// we add 1 to get the next character, also max len is 16
		name = (char*)(*localPlayer + offsets::ac_name + i);
		std::cout << *(name);
		//might add some random string generator later on
		//would be cool to see the name changing constantly
	}
}

void Main(const HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	//PlaySound(INJECT, NULL, SND_SYNC);
	hooks::Setup();
	int *localPlayerPtr, *ammo_mtp, *ammo_mk, *health, *frags, *playersNum, *grenades;
	int *entityListPtr;
	float *x,  *y,  *z;//player's coords


	int base	   = (int)GetModuleHandle(NULL);
	localPlayerPtr = (int*)(base + offsets::ac_localPlayer);
	entityListPtr  = (int*)(base + offsets::ac_entityList);

#ifdef _DEBUG
	std::cout << "------------------------CURRENT ADRESSES-------------------------\n";
	std::cout << "localPlayer - [ " << std::hex << localPlayerPtr << "]\n";
	std::cout << "entityList -  [ " << std::hex << entityListPtr << "]\n";
	std::cout << "ammo  - [ " << std::hex << (int*)(*localPlayerPtr + offsets::ac_ammoMTP)   << " ]\n";
	std::cout << "health- [ " << std::hex << (int*)(*localPlayerPtr + offsets::ac_health) << " ]\n";
	std::cout << "frags - [ " << std::hex << (int*)(*localPlayerPtr + offsets::ac_frags)  << " ]\n";
	std::cout << "   x  - [ " << std::hex << (float*)(*localPlayerPtr + offsets::ac_x)    << " ]\n";
	std::cout << "   y  - [ " << std::hex << (float*)(*localPlayerPtr + offsets::ac_y)    << " ]\n";
	std::cout << "   z  - [ " << std::hex << (float*)(*localPlayerPtr + offsets::ac_z)    << " ]\n";
	std::cout << "players num - [" << std::hex << (int*)(base + offsets::ac_playerNumber) << " ]\n";
	std::cout << "\n------------------------CURRENT ADRESSES-------------------------\n";
#endif

	std::cout << "\n\n----------------[Cheat table]----------------\n" <<
		"num2 - infinite ammo\nnum1 - infinite health\nnum3 - set health to 9.000\nnum4 - save teleport location" <<
		"\nnum5 - teleport to the last saved location\nnum6 - no recoil\n[USERNAME] - ";

	PrintName(localPlayerPtr);
	std::cout<< "\n\n----------------[Cheat table]----------------\n";

	float* teleportLocation = new float [3] ;
	int healthValue = 100;
	bool bHealth = false, bAmmo = false;

	// since we have enable all hooks in hooks::Setup()
	// all the bools must be set to true
	bool bRecoil = true;

	std::cout << '\n';

	while (!GetAsyncKeyState(VK_END))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		//so we get the pointer to the local player
		//we dereference it so we can add the respective
		//offsets and then initialize the pointer to that
		//memory adress in which, let's say ammo value,
		//is stored in the game
		ammo_mtp = (int*)(*localPlayerPtr + offsets::ac_ammoMTP);
		ammo_mk  = (int*)(*localPlayerPtr + offsets::ac_ammoMK);
		health   = (int*)(*localPlayerPtr + offsets::ac_health);
		frags    = (int*)(*localPlayerPtr + offsets::ac_frags);
		grenades = (int*)(*localPlayerPtr + offsets::ac_grenades);
		x = (float*)(*localPlayerPtr + offsets::ac_x);
		y = (float*)(*localPlayerPtr + offsets::ac_y);
		z = (float*)(*localPlayerPtr + offsets::ac_z);
		
		//enable/ disable infinite health
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			bHealth = !bHealth;
			bHealth == 1 ? (std::cout << "\n[infinite health enabled]\n") : (std::cout << "\n[infinite health disabled]\n");
		}

		//enable/ disable infinite ammo
		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			bAmmo = !bAmmo;
			*grenades = 999;
			bAmmo == 1 ? (std::cout << "\n[infinite ammo enabled]\n") : (std::cout << "\n[infinite ammo disabled]\n");
		}

		//set health value to 9.000
		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			//if we dont have infinite health enabled we just set the health to 9.000 and continue
			if (!bHealth)
			{
				*health = 9000;
			}
			healthValue = 9000;
		}

		//save teleport location
		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			//saving coords
			SaveLocation(teleportLocation, x, y, z);
		}

		//teleport to the location previously saved
		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			TeleportTo(teleportLocation, x, y, z);
		}

		//enable or disable no recoil hook
		if (GetAsyncKeyState(VK_NUMPAD6) & 1)
		{
			bRecoil = !bRecoil;
			bRecoil == 1 ? (std::cout << "\n[no recoil enabled]\n") : (std::cout << "\n[no recoil disabled]\n");
			bRecoil == 1 ? (MH_EnableHook(hooks::pRecoilTarget)) : (MH_DisableHook(hooks::pRecoilTarget));
		}

		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			//set all entities health to 0
			//still needs 1 hit to die
			EntityListHealth(entityListPtr);
		}

		//infinite health
		Health(bHealth, health, healthValue);

		// infinite ammo
		Ammo(bAmmo, ammo_mtp);
		Ammo(bAmmo, ammo_mk);
	}


	if (f)
	{
		fclose(f);
	}
	hooks::Destroy();
	//PlaySound(UINJECT, NULL, SND_SYNC);
	delete[] teleportLocation;
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD reason_for_call, void* reserved)
{
	switch (reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)(Main), hModule, NULL, nullptr);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}