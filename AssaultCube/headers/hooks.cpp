#include<iostream>
#include<MinHook.h>
#include"hooks.h"

void hooks::Setup()
{

	MH_Initialize();

	// MH_CreateHook(void**(target), &myFunc, void**(&original) )
    if (MH_CreateHook(reinterpret_cast<void**>(noRecoilTarget), &DetourRecoil, reinterpret_cast<void**>(&noRecoil)) != MH_OK)
    {
        std::cout << "\nsomething went wrong\n";
    }
    else
    {
        std::cout << "\nfunction hooked << recoil >>\n";
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

int __stdcall hooks::DetourWglSwapBuffers(HDC p1)
{
	// magic happens here

	//--------------------
	return WglSwapBuffersOriginal(p1);
}

int __stdcall hooks::DetourRecoil()
{
	_asm
	{
		ret 0x08;
	}
}

