#pragma once
#include<iostream>
#include"../minhook/MinHook.h"

namespace hooks
{
	// here we declare the function pointer for recoil
	typedef int(__thiscall* recoil)(void* pThis, float* x, float* y);
	inline recoil RecoilOriginal = nullptr;
	inline recoil RecoilTarget = reinterpret_cast<recoil>(0x004C6A20);
	// it get's called every time we shoot and returns 8
	// so by returning 8 at the start of the function
	// we no longer have any recoil
	void __stdcall DetourRecoil(float* x, float* y)
	{
		// this code is executed at the start of the function where sub esp, 28 should be
		_asm ret 8;
	}


	typedef int(__stdcall* wglSwapBuffers)(HDC p1);
	inline wglSwapBuffers WglSwapBuffersOriginal = nullptr;
	inline wglSwapBuffers WglSwapBuffersTarget = reinterpret_cast<wglSwapBuffers>(GetProcAddress(GetModuleHandle("OPENGL32.dll"), "wglSwapBuffers"));
	int DetourWglSwapBuffers(HDC p1)
	{
		// magic happens here

		//--------------------
		return WglSwapBuffersOriginal(p1);
	}

	void Setup()
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

	void Destroy()
	{
		// just disabling and removing all hooks so that we don't have code
		// lingering after the dll is uninjected
		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}
}

