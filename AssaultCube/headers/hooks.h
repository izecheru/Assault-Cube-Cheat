#pragma once
#include<iostream>
#include"../minhook/MinHook.h"

namespace hooks
{
	// here we declare the function pointer for recoil
	typedef int(__thiscall* recoil)(float* x, float* y);
	inline recoil pRecoil = nullptr;
	inline recoil pRecoilTarget = reinterpret_cast<recoil>(0x004C6A20);
	
	// it get's called every time we shoot and returns 8
	// so by returning 8 at the start of the function
	// we no longer have any recoil code
	void __fastcall detourRecoil(float* x, float* y)
	{
		// this code is executed at the start of the function where sub esp, 28 should be
		_asm ret 8;
	}

	void Setup()
	{
		MH_Initialize();

		bool flag = false;
		// create hook takes as parameters the adress of the target function, the function we want to execute instead and then a nullptr 
		// that has the same type as the target
		if (MH_CreateHook(reinterpret_cast<void**>(pRecoilTarget), &detourRecoil, reinterpret_cast<void**>(&pRecoil)) != MH_OK)
		{
			std::cout << "\nsomething went wrong\n";
			flag = true;
		}
		else
		{
			std::cout << "\nfunction hooked >> recoil\n";
		}

		// if we didnt fail anywhere than we proceed and enable all hooks
		if (flag != true)
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