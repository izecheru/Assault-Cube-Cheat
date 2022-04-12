#include<Windows.h>
#include<iostream>
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<thread>

#include"../headers/localPlayer.h"
#include "../headers/entities.h"
#include "../cheats/infiniteStuff.h"
#include "../cheats/teleport.h"
#include "../headers/hooks.h"
#include "../cheats/lookAway.h"

#pragma comment(lib, "Winmm.lib")

#define UINJECT "E:/repository/repo/audio/uninject.wav"
#define INJECT "E:/repository/repo/audio/inject.wav"

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

	LocalPlayer* localPlayer = *(LocalPlayer**)(base + offsets::ac_localPlayer);
	PrintName(localPlayer);

	// some bools for functions that have enable/ disable state
	bool bHealth = false, bAmmo = false;
	// if we didn't saved the location at least once than we surely
	// don't want to teleport to 2.000000e-10 or something like that
	bool savedOnce = false;

	// since we have enable all hooks in hooks::Setup()
	// all the bools must be set to true
	bool bRecoil = true;
	std::cout << '\n';

	// vector used for location saving and teleporting
	Vector3* vec = new Vector3;

	while (!GetAsyncKeyState(VK_END))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		
		// enable/ disable recoil
		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			bRecoil = !bRecoil;
			bRecoil == 1 ? (std::cout << "\n[no recoil enabled]\n") : (std::cout << "\n[no recoil disabled]\n");
			bRecoil == 1 ? (MH_EnableHook(hooks::pRecoilTarget)) : (MH_DisableHook(hooks::pRecoilTarget));
		}

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
			teleport::SaveLocation(vec, localPlayer);
		}

		// teleport to a saved location
		if (GetAsyncKeyState(VK_NUMPAD4) & 1 && savedOnce==true)
		{
			teleport::TeleportTo(vec, localPlayer);
		}

		// the sniper, pistol or shotgun are click to shoot once, so if i keep delete pressed
		// i shoot untill i release delete, this combined with wait = 0 result in a laser type weapon
		// be carefull tho, without recoil you are going to fly like a bird and mby hit your head
		if (GetAsyncKeyState(VK_DELETE))
		{
			localPlayer->forceAttack = 1;
		}
		else
		{
			localPlayer->forceAttack = 0;
		}

		if (GetAsyncKeyState(VK_NUMPAD6)&1)
		{
			lookAway::Look(localPlayer);
		}

		// functions for infinite things like ammo, health
		// they are in enabled, disabled state
		Ammo(localPlayer, bAmmo);
		Health(localPlayer, bHealth);

		localPlayer->grenadeWait = 0;
		localPlayer->rifleWait = 0;
		localPlayer->sniperWait = 0;
		localPlayer->pistolWait = 0;
		localPlayer->shotgunWait = 0;
		localPlayer->subMachineGunWait = 0;
	}


	if (f)
	{
		fclose(f);
	}
	hooks::Destroy();
	//PlaySound(UINJECT, NULL, SND_SYNC);
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