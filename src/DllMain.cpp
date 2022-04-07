#include<Windows.h>
#include<iostream>
#include<Windows.h>
#include<iostream>
#include<fstream>
#pragma comment(lib, "Winmm.lib")


#define UINJECT "E:/repository/repo/audio/uninject.wav"
#define INJECT "E:/repository/repo/audio/inject.wav"

/*
offsets
---coords---
x - 0x0004
y - 0x0008
z - 0x000C
------------
health - 0x00EC
ammo - 0x140
frags - 0x01DC
localPlayer - 0x17B264 0x187C0C 0x17B370
*/



void init(const HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	//PlaySound(INJECT, NULL, SND_SYNC);

	uintptr_t* localPlayer; uintptr_t* ammo; uintptr_t* health; uintptr_t* frags;
	float* x; float* y; float* z;

	uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
	localPlayer = (uintptr_t*)(base + 0x17B370);
	bool bHealth = false, bAmmo = false;
	std::cout << "[Cheat table, numpad 2 - ammo, numpad 1 - health\n";
	while (!GetAsyncKeyState(VK_END))
	{
		Sleep(100);
		//so we get the pointer to the local player
		//we dereference it so we can add the respective
		//offsets and then initialize the pointer to that
		//memory adress in which, let's say ammo value,
		//is stored in the game
		ammo = (uintptr_t*)(*(localPlayer)+0x140);
		health = (uintptr_t*)(*(localPlayer)+0x00EC);
		frags = (uintptr_t*)(*(localPlayer)+0x01DC);
		x = (float*)(*(localPlayer)+0x0004);
		y = (float*)(*(localPlayer)+0x0008);
		z = (float*)(*(localPlayer)+0x000C);

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			bHealth = !bHealth;
			bHealth == 1 ? (std::cout << "\n[infinite health enabled]\n") : (std::cout << "\n[infinite health disabled]\n");
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			bAmmo = !bAmmo;
			bAmmo == 1 ? (std::cout << "\n[infinite ammo enabled]\n") : (std::cout << "\n[infinite ammo disabled]\n");
		}
		if (GetAsyncKeyState(VK_NUMPAD8) & 1)
		{
			//showing coords
			std::cout << "[x,y,z]" << "[ " << *(x) << ", " << *(y) << ", " << *(z) << " ]\n";
		}

		if (bHealth)
		{

			//if infinite health is enabled
			//every 10 milliseconds we set
			//the health to 100
			*(health) = 100;
		}

		if (bAmmo)
		{
			//if infinite amkmo is enabled
			//every 10 milliseconds we set
			//the amoo to 20
			//need to find the other guns
			//ammo adresses since each
			//gun has a different ammo
			//memory adress storage and values
			*(ammo) = 20;
		}
	}


	if (f)
	{
		fclose(f);
	}

	//PlaySound(UINJECT, NULL, SND_SYNC);
	FreeConsole();
	Sleep(100);
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