#pragma once

#include <iostream>
#include<Windows.h>

#include "Offsets.h"
#include"Cheats.h"

bool Detour(BYTE* Func, BYTE* HookAddress, UINT length);
BYTE* Trampoline_Hook(BYTE* addresstoHook, BYTE* hookfunction, uintptr_t length);

struct Hook
{
	bool status{ false };
	BYTE* hook_function{ nullptr }; // This is the detour function
	BYTE* original_function{ nullptr }; // This is the address to hook
	BYTE* ptr_2_gateway_ptr{ nullptr };
	uintptr_t length{ 0 };

	BYTE originalBytes[10]{ 0 };

	Hook(BYTE* Function = 0, BYTE* Address = 0, BYTE* ptr2_gateway = 0, uintptr_t length = 0);
	Hook(BYTE* Function, const char*  moduleName, const char* exportName, BYTE* ptr2_gateway, uintptr_t length);

	void Enable();
	void Disable();
	void Toggle();
};

static Hook swapBuffer;
static Hook silentaim_hook;

typedef void(__thiscall* template_shootFunc)(DWORD*, vec3&);

template_shootFunc original_shootFunc;
void __fastcall hooked_shootFunc(DWORD* This, void* _EDX, vec3& endPoint);

