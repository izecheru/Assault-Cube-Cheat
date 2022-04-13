#pragma once
#include<MinHook.h>

namespace hooks
{
	// here we declare the function pointer for recoil
	typedef int(__thiscall* recoil)(void* pThis, float* x, float* y);
	inline recoil RecoilOriginal = nullptr;
	inline recoil RecoilTarget = reinterpret_cast<recoil>(0x004C6A20);

	void __stdcall DetourRecoil(float* x, float* y);

	// opengl hook for esp, need to use it later
	typedef int(__stdcall* wglSwapBuffers)(HDC p1);
	inline wglSwapBuffers WglSwapBuffersOriginal = nullptr;
	inline wglSwapBuffers WglSwapBuffersTarget = reinterpret_cast<wglSwapBuffers>(GetProcAddress(GetModuleHandle("OPENGL32.dll"), "wglSwapBuffers"));

	int __stdcall DetourWglSwapBuffers(HDC p1);

	void Setup();
	void Destroy();
}

