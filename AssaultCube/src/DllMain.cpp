#include<Windows.h>
#include<iostream>
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<thread>
#pragma comment(lib, "Winmm.lib")

#define UINJECT "E:/repository/repo/audio/uninject.wav"
#define INJECT "E:/repository/repo/audio/inject.wav"

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

namespace Offsets
{
	constexpr auto ac_localPlayer = 0x187C0C;
	constexpr auto ac_name = 0x205;
	constexpr auto ac_ammo = 0x140;
	constexpr auto ac_health = 0xEC;
	constexpr auto ac_frags = 0x1DC;
	constexpr auto ac_entityList= 0x187C10;

	//since the pitch is up and down we also have
	//negative values so must not do uint
	constexpr auto ac_pitch = 0x0038;
	constexpr auto ac_yaw = 0x0034;
	constexpr auto ac_roll = 0;
	
	//-------------------------COORDS-------------------------------\\

	/*
	after more research i found some values
	that after changing them i teleport ac might have some console stuff
	what i mean is that i may have found just some 
	printed values not the real ones that are related to the player
	*/
	
	constexpr auto ac_x = 0x0028;
	constexpr auto ac_y = 0x002C;
	constexpr auto ac_z = 0x0030;
	
	constexpr auto ac_weird_x = 0x0004;
	constexpr auto ac_weird_y = 0x0008;
	constexpr auto ac_weird_z = 0x000C;
	//-------------------------COORDS-------------------------------
}

void Main(const HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	//PlaySound(INJECT, NULL, SND_SYNC);

	int* localPlayerPtr, *ammo, *health, *frags;
	int* entityListPtr;
	char* name; char* nameArr = new char[17];
	float* x,  *y,  *z;


	int base	   = (int)GetModuleHandle(NULL);
	localPlayerPtr = (int*)(base + Offsets::ac_localPlayer);
	entityListPtr  = (int*)(base + Offsets::ac_entityList);
	std::cout << "------------------------CURRENT ADRESSES-------------------------\n";
	std::cout << "localPlayerPtr - [ " << std::hex << *localPlayerPtr << "]\n";
	std::cout << "entityListPtr -  [ " << std::hex << *entityListPtr << "]\n";
	std::cout << "ammo  - [ " << std::hex << (int*)(*localPlayerPtr + Offsets::ac_ammo)   << " ]\n";
	std::cout << "health- [ " << std::hex << (int*)(*localPlayerPtr + Offsets::ac_health) << " ]\n";
	std::cout << "frags - [ " << std::hex << (int*)(*localPlayerPtr + Offsets::ac_frags)  << " ]\n";
	std::cout << "   x  - [ " << std::hex << (float*)(*localPlayerPtr + Offsets::ac_x)    << " ]\n";
	std::cout << "   y  - [ " << std::hex << (float*)(*localPlayerPtr + Offsets::ac_y)    << " ]\n";
	std::cout << "   z  - [ " << std::hex << (float*)(*localPlayerPtr + Offsets::ac_z)    << " ]\n";
	std::cout << "\n------------------------CURRENT ADRESSES-------------------------\n";

	bool bHealth = false, bAmmo = false;
	std::cout << "[Cheat table, numpad 2 - ammo, numpad 1 - health, numpad 3 - set health to 9k\nnumpad 4 - save teleport location,"<<
				"numpad 5 - teleport to the last saved location\n[USER] - ";

	float* teleportLocation = new float[3];
	for (int i = 0; i < 16; i++)
	{
		// since char is 1 byte we get the first character adress and then
		// we add 1 to get the next character, max len is 16
		name = (char*)(localPlayerPtr+Offsets::ac_name+i);
		nameArr[i] = *(name); //in case we need the name anywere else
		std::cout << *(name);
		//might add some random string generator later on
		//would be cool to see the name changing constantly
	}
	int healthValue = 100;
	std::cout << '\n';
	while (!GetAsyncKeyState(VK_END))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		//so we get the pointer to the local player
		//we dereference it so we can add the respective
		//offsets and then initialize the pointer to that
		//memory adress in which, let's say ammo value,
		//is stored in the game
		ammo   = (int*)(*localPlayerPtr + Offsets::ac_ammo);
		health = (int*)(*localPlayerPtr + Offsets::ac_health);
		frags  = (int*)(*localPlayerPtr + Offsets::ac_frags);
		x = (float*)( *localPlayerPtr + Offsets::ac_x);
		y = (float*)( *localPlayerPtr + Offsets::ac_y);
		z = (float*)( *localPlayerPtr + Offsets::ac_z);
		
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
			bAmmo == 1 ? (std::cout << "\n[infinite ammo enabled]\n") : (std::cout << "\n[infinite ammo disabled]\n");
		}

		//set health value to 9k
		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			healthValue = 9000;
		}

		//save teleport location
		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			//saving coords
			teleportLocation[0] = *x;
			teleportLocation[1] = *y;
			teleportLocation[2] = *z;
			std::cout << "\ncoords saved [" << *x << ", " << *y << ", " << *z << "]\n";
		}

		//teleport to the location previously saved
		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			//showing coords
			*x = teleportLocation[0];
			*y = teleportLocation[1];
			*z = teleportLocation[2];
			std::cout << "\nteleported to saved location [" << *x << ", " << *y << ", " << *z << "]\n";
		}

		//infinite health
		if (bHealth)
		{
			*health = healthValue;
		}

		// infinite ammo
		if (bAmmo)
		{
			*ammo = 20;
		}
	}


	if (f)
	{
		fclose(f);
	}

	delete[] teleportLocation;
	//PlaySound(UINJECT, NULL, SND_SYNC);
	FreeConsole();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
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