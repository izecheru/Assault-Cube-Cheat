#pragma once

namespace hooks
{
	// opengl hook for esp, need to use it later
	typedef int(__stdcall* wglSwapBuffers)(HDC p1);
	inline wglSwapBuffers WglSwapBuffersOriginal = nullptr;
	inline wglSwapBuffers WglSwapBuffersTarget	 = reinterpret_cast<wglSwapBuffers>(GetProcAddress(GetModuleHandle("OPENGL32.dll"), "wglSwapBuffers"));
	int __stdcall DetourWglSwapBuffers(HDC p1);

	// here we declare the function pointer for recoil
	typedef int(__thiscall* recoil)(void* ptr, float* x, float* y);
	inline recoil noRecoil		 = nullptr;
	inline recoil noRecoilTarget = reinterpret_cast<recoil>(0x004C6A20);
	int __stdcall DetourRecoil();

	void Setup();
	void Destroy();
}