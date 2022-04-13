#include <Windows.h>
#include <iostream>
#include <fstream>
#include <thread>

#include "../headers/entity.h"
#include "../headers/hooks.h"
#include "../cheats/infiniteStuff.h"
#include "../cheats/teleport.h"
#include "../cheats/lookAway.h"

void Main(HMODULE hModule);

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

void Main(const HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	//PlaySound(INJECT, NULL, SND_SYNC);
	hooks::Setup();

	// adress of the app in memory
	// we need it so we can add the local player offset
	int base = (int)GetModuleHandle(NULL);


	// --------------- LOCAL PLAYER AND ENT LIST INITIALIZATION ---------------  
	PlayerEntity* localPlayer = *(PlayerEntity**)(base + 0x187C0C);
	EntList* entityList = *(EntList**)(base + 0x187C10);
	// --------------- LOCAL PLAYER AND ENT LIST INITIALIZATION ---------------  


	PrintName(localPlayer);
	// some bools for functions that have enable/ disable state
	bool bHealth = false, bAmmo = false;

	// if we didn't saved the location at least once than we surely
	// don't want to teleport to 2.000000e-10 or something like that
	bool savedOnce = false;

	// low gravity bool for enable/ disable state
	bool lowGrav = false;

	// since we have enable all hooks in hooks::Setup()
	// all the bools must be set to true
	bool bRecoil = true;
	std::cout << '\n';

	// vector used for location saving and teleporting
	Vector3* teleportLocation = new Vector3;
	Vector3* botTeleportLocation = new Vector3;
	while (!GetAsyncKeyState(VK_END))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		// enable/ disable infinite health
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			bHealth = !bHealth;
			bHealth == 1 ? (std::cout << "\n[infinite health enabled]\n") : (std::cout << "\n[infinite health disabled]\n");
		}

		//enale/ disable infinite ammo
		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			bAmmo = !bAmmo;
			bAmmo == 1 ? (std::cout << "\n[infinite ammo enabled]\n") : (std::cout << "\n[infinite ammo disabled]\n");
		}

		// save location so that we can teleport to it
		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			savedOnce = !savedOnce;
			teleport::SaveLocation(teleportLocation, localPlayer);
		}

		// teleport to a saved location
		if (GetAsyncKeyState(VK_NUMPAD4) & 1 && savedOnce==true)
		{
			teleport::TeleportTo(teleportLocation, localPlayer);
		}

		// enable/ disable recoil
		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			bRecoil = !bRecoil;
			bRecoil == 1 ? (std::cout << "\n[no recoil enabled]\n") : (std::cout << "\n[no recoil disabled]\n");
			bRecoil == 1 ? (MH_EnableHook(hooks::RecoilTarget)) : (MH_DisableHook(hooks::RecoilTarget));
		}

		//set hp to 100
		if (GetAsyncKeyState(VK_NUMPAD6) & 1)
		{
			localPlayer->health = 100;
		}

		// look in a random direction
		if (GetAsyncKeyState(VK_NUMPAD7)&1)
		{
			lookAway::Look(localPlayer);
		}

		// just add some hp
		if (GetAsyncKeyState(VK_ADD) & 1)
		{
			localPlayer->health += 30;
		}

		// low gravity
		if (GetAsyncKeyState(0x47) & 1)
		{
			lowGrav = !lowGrav;
			lowGrav == 1 ? (std::cout << "\n[low gravity enabled]\n") : (std::cout << "\n[low gravity disabled]\n");
		}
		if (lowGrav)
		{
			localPlayer->lowGravity = 0;
			if (GetAsyncKeyState(VK_SPACE)&1)
			{
				localPlayer->location.z += 0.1;
			}
		}

		// the sniper, pistol or shotgun are click to shoot once, so if i keep delete pressed
		// i shoot untill i release delete, this combined with wait = 0 result in a laser type weapon
		// be carefull tho, without recoil you are going to fly like a rocket and mby hit your head
		if (GetAsyncKeyState(VK_DELETE))
		{
			localPlayer->forceAttack = 1;
		}

		// get the closest entityList ptr to our local player
		if (GetAsyncKeyState(VK_NUMPAD9) & 1)
		{
			PlayerEntity* closestOne = ClosestEntity(localPlayer, entityList);
			PrintName(closestOne);
			//teleport::TeleportEntity(teleportLocation, closestOne);
			teleport::TeleportAllEntitoes(botTeleportLocation, entityList);
		}

		// print out all entities names
		if (GetAsyncKeyState(VK_INSERT)&1)
		{
			for (int i = 1; i <=31; i++)
			{
				// since the first index is nullptr if we try to read from it 
				// we will crash the game, keep that in mind when reversing other games
				// a simple if(something==nullptr) can save you a lot of time
				if (entityList->vector[i] == nullptr)
				{
					std::cout << "\ndumb dumb, das a nullptr\n";
					continue;
				}
				std::cout << "entityList - " << i << '\n';
				PrintName(entityList->vector[i]);
			}
		}

		// functions for infinite things like ammo, health
		// they are in enabled, disabled state
		Ammo(localPlayer, bAmmo);
		Health(localPlayer, bHealth);
		//----------------------------

		localPlayer->grenadeWait = 0;
		localPlayer->rifleWait = 0;
		localPlayer->sniperWait = 0;
		localPlayer->pistolWait = 0;
		localPlayer->shotgunWait = 0;
		localPlayer->subMachineGunWait = 0;
		localPlayer->carbineWait = 0;
	}


	if (f)
	{
		fclose(f);
	}

	// getting rid of hooks before closing the thread
	hooks::Destroy();

	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}
