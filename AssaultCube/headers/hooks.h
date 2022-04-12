#pragma once
#include<iostream>
#include"../minhook/MinHook.h"

namespace hooks
{
	// here we declare the function pointer for recoil
	typedef int(__thiscall* recoil)(void* pThis, float* x, float* y);
	inline recoil pRecoil = nullptr;
	inline recoil pRecoilTarget = reinterpret_cast<recoil>(0x004C6A20);
	// it get's called every time we shoot and returns 8
	// so by returning 8 at the start of the function
	// we no longer have any recoil code
	void __stdcall detourRecoil(float* x, float* y)
	{
		// this code is executed at the start of the function where sub esp, 28 should be
		_asm ret 8;
	}

	//typedef int(__thiscall* flashtime)(void* ptr);
	//inline flashtime pFlashTime = nullptr;
	//inline flashtime pFlashTimeTarget = reinterpret_cast<flashtime>(0x004C66F0);

	//void __stdcall hooks::detourFlashTime()
	//{
	//	std::cout << "function called\n";
	//	return;
	//}

	typedef int(__thiscall* fire)(void* pThis, int* a, float* b,  int* c);
	inline fire pFire = nullptr;
	inline fire pFireTarget = reinterpret_cast<fire>(0x004C6FC0);

	//not working
	void __stdcall detourFire()
	{
		//_asm _90;
	}

	/*typedef int(__thiscall* renderaimhelp)(void* ptr, bool enalbe);
	inline renderaimhelp pRenderAimHelp = nullptr;
	inline renderaimhelp pRenderAimHelpTarget = reinterpret_cast<renderaimhelp>(0x004C6700);

	int __fastcall detourAimHelp(void* ptr, bool enable)
	{
		std::cout << "merge\n" << '\n';
		return pRenderAimHelp(ptr, enable);
	}*/

	bool CheckFlags(bool* flags, int hooksNum)
	{
		for (int i = 0; i < hooksNum; i++)
		{
			if (flags[i] == true)
			{
				return true;
			}
		}
		return false;
	}

	void Setup()
	{
		MH_Initialize();

		bool* flags = new bool[4];
		// MH_CreateHook(void**(target), &myFunc, void**(&original) )
		if (MH_CreateHook(reinterpret_cast<void**>(pRecoilTarget), &detourRecoil, reinterpret_cast<void**>(&pRecoil)) != MH_OK)
		{
			std::cout << "\nsomething went wrong\n";
			flags[0] = true;
		}
		else
		{
			std::cout << "\nfunction hooked >> recoil\n";
		}
		// if we didnt fail anywhere than we proceed and enable all hooks
		if (CheckFlags(flags,3)==false)
		{
			MH_EnableHook(MH_ALL_HOOKS);
		}
	}

	void Destroy()
	{
		// just disabling and removing all hooks so that we don't have code
		// lingering after the dll is uninjected
		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}
}

