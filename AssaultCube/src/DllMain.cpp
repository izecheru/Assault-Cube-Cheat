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

namespace Offsets
{
	constexpr auto ac_localPlayer = 0x187C0C;
	// -------------player variables-------------
	constexpr auto ac_name      = 0x205;
	constexpr auto ac_ammoMTP   = 0x140;
	constexpr auto ac_ammoMK    = 0x012c;
	constexpr auto ac_health    = 0xEC;
	constexpr auto ac_frags		= 0x1DC;
	constexpr auto ac_grenades  = 0x0144;
	// -------------player variables-------------


	constexpr auto ac_entityList= 0x187C10;

	//might actually be max players but since the game
	//fills the lobby i dont currently know this
	constexpr auto ac_playerNumber = 0x187C18;

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

void PrintName(int* localPlayerPtr)
{
	char* name;
	for (int i = 0; i < 16; i++)
	{
		// since char is 1 byte we get the first character adress and then
		// we add 1 to get the next character, max len is 16
		name = (char*)(*localPlayerPtr + Offsets::ac_name + i);
		std::cout << *(name);
		//might add some random string generator later on
		//would be cool to see the name changing constantly
	}
}

void Health(bool enabled, int* healthPtr, int ammount)
{
	if (enabled) 
	{
		*(healthPtr) = ammount;
	}
}

void Ammo(bool enabled, int* ammoPtr, int ammount = 20)
{
	if(enabled)
	{
		*ammoPtr = ammount;
	}
}

void TeleportTo(float* teleportLocation, float* x, float* y, float* z)
{//coords are x y z in this order
	*x = teleportLocation[0];
	*y = teleportLocation[1];
	*z = teleportLocation[2];
	std::cout << "\nteleported to saved location [" << *x << ", " << *y << ", " << *z << "]\n";
}

void SaveLocation(float* teleportLocation, float* x, float* y, float* z)
{//coords are x y z in this order
	teleportLocation[0] = *x;
	teleportLocation[1] = *y;
	teleportLocation[2] = *z;
	std::cout << "\ncoords saved [" << *x << ", " << *y << ", " << *z << "]\n";
}

//currently not working, might not be pointing to the right memory adress
void EntityListHealth(int* entityListPtr)
{
	std::cout << '\n';
	int* temp;
	for (int i = 4; i < 32; i += 4)
	{
		temp = entityListPtr + i;
		temp = temp + Offsets::ac_health;
		std::cout << temp <<'\n';
	}
}

void Main(const HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	//PlaySound(INJECT, NULL, SND_SYNC);

	int* localPlayerPtr, *ammo_mtp, *ammo_mk, *health, *frags, *playersNum, *grenades;
	int* entityListPtr;
	float* x,  *y,  *z;//player's coords


	int base	   = (int)GetModuleHandle(NULL);
	localPlayerPtr = (int*)(base + Offsets::ac_localPlayer);
	entityListPtr  = (int*)(base + Offsets::ac_entityList);

#ifdef _DEBUG
	std::cout << "------------------------CURRENT ADRESSES-------------------------\n";
	std::cout << "localPlayerPtr - [ " << std::hex << *localPlayerPtr << "]\n";
	std::cout << "entityListPtr -  [ " << std::hex << *entityListPtr << "]\n";
	std::cout << "ammo  - [ " << std::hex << (int*)(*localPlayerPtr + Offsets::ac_ammo)   << " ]\n";
	std::cout << "health- [ " << std::hex << (int*)(*localPlayerPtr + Offsets::ac_health) << " ]\n";
	std::cout << "frags - [ " << std::hex << (int*)(*localPlayerPtr + Offsets::ac_frags)  << " ]\n";
	std::cout << "   x  - [ " << std::hex << (float*)(*localPlayerPtr + Offsets::ac_x)    << " ]\n";
	std::cout << "   y  - [ " << std::hex << (float*)(*localPlayerPtr + Offsets::ac_y)    << " ]\n";
	std::cout << "   z  - [ " << std::hex << (float*)(*localPlayerPtr + Offsets::ac_z)    << " ]\n";
	std::cout << "players num - [" << std::hex << (int*)(base + Offsets::ac_playerNumber) << " ]\n";
	std::cout << "\n------------------------CURRENT ADRESSES-------------------------\n";
#endif

	std::cout << "\n\n----------------[Cheat table]----------------\n" <<
		"num2 - infinite ammo\nnum1 - infinite health\nnum3 - set health to 9.000\nnum4 - save teleport location" <<
		"\nnum5 - teleport to the last saved location\n[USERNAME] - ";
	PrintName(localPlayerPtr);
	std::cout<< "\n\n----------------[Cheat table]----------------\n";
	float* teleportLocation = new float [3] ;
	int healthValue = 100;
	bool bHealth = false, bAmmo = false;
	std::cout << '\n';
	EntityListHealth(entityListPtr);
	while (!GetAsyncKeyState(VK_END))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		//so we get the pointer to the local player
		//we dereference it so we can add the respective
		//offsets and then initialize the pointer to that
		//memory adress in which, let's say ammo value,
		//is stored in the game
		ammo_mtp = (int*)(*localPlayerPtr + Offsets::ac_ammoMTP);
		ammo_mk = (int*)(*localPlayerPtr + Offsets::ac_ammoMK);
		health   = (int*)(*localPlayerPtr + Offsets::ac_health);
		frags    = (int*)(*localPlayerPtr + Offsets::ac_frags);
		grenades = (int*)(*localPlayerPtr + Offsets::ac_grenades);
		x = (float*)( *localPlayerPtr + Offsets::ac_x);
		y = (float*)( *localPlayerPtr + Offsets::ac_y);
		z = (float*)( *localPlayerPtr + Offsets::ac_z);
		
		//enable/ disable infinite health
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			bHealth = !bHealth;
			//bHealth == 1 ? (std::cout << "\n[infinite health enabled]\n") : (std::cout << "\n[infinite health disabled]\n");
		}

		//enable/ disable infinite ammo
		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			bAmmo = !bAmmo;
			*grenades = 999;
			//bAmmo == 1 ? (std::cout << "\n[infinite ammo enabled]\n") : (std::cout << "\n[infinite ammo disabled]\n");
		}

		//set health value to 9.000
		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			//std::cout << "\nhealth value set to 9.000\n";
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

	//PlaySound(UINJECT, NULL, SND_SYNC);
	delete[] teleportLocation;
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