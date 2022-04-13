#pragma once
#include"hooks.h"

	void __stdcall hooks::DetourRecoil(float* x, float* y)
	{
		// this code is executed at the start of the function where sub esp, 28 should be
		_asm ret 8;
	}

	int __stdcall hooks::DetourWglSwapBuffers(HDC p1)
	{
		// magic happens here

		//--------------------
		return WglSwapBuffersOriginal(p1);
	}

	void hooks::Setup()
	{
		MH_Initialize();

		// MH_CreateHook(void**(target), &myFunc, void**(&original) )
		if (MH_CreateHook(reinterpret_cast<void**>(RecoilTarget), &DetourRecoil, reinterpret_cast<void**>(&RecoilOriginal)) != MH_OK)
		{
			std::cout << "\nsomething went wrong\n";
		}
		else
		{
			std::cout << "\nfunction hooked >> recoil <<\n";
		}
		if (MH_CreateHook(reinterpret_cast<void**>(WglSwapBuffersTarget), &DetourWglSwapBuffers, reinterpret_cast<void**>(&WglSwapBuffersOriginal)) != MH_OK)
		{
			std::cout << "\nsomething went wrong\n";
		}
		else
		{
			std::cout << "\nfunction hooked >> wglSwapBuffers <<\n";
		}
		MH_EnableHook(MH_ALL_HOOKS);
	}

	void hooks::Destroy()
	{
		// just disabling and removing all hooks so that we don't have code
		// lingering after the dll is uninjected
		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}