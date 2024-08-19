#include"Hook.h"
#include "Offsets.h"
#include "Cheats.h"
bool Detour(BYTE* Func, BYTE* HookAddress, UINT length)
{
	if (length >= 5)
	{
		DWORD oldprotect;

		VirtualProtect(HookAddress, length, PAGE_EXECUTE_READWRITE, &oldprotect); // Allows us to edit the code page part of memory
		// We will set each byte of how much bytes we take to nop, just to make sure nothing crashes our game

		DWORD relativeAddress = ((DWORD)Func - (DWORD)HookAddress) - 5; // This is how many bytes we will need to jump, we -5 because the instruction to jmp itself is 5 bytes
		*(BYTE*)HookAddress = 0xE9; // JMP, we do *byte because JMP instruction takes one byte
		*(DWORD*)((DWORD)HookAddress + 1) = relativeAddress; // completes our jump instruction by adding the relative address to jmp so the instruction will look like JMP relativeadresss now

		VirtualProtect(HookAddress, length, oldprotect, &oldprotect);
		return true;
	}
	else
	{
		return false;
	}
}

BYTE* Trampoline_Hook(BYTE* addresstoHook, BYTE* hookfunction, uintptr_t length)
{
	if (length >= 5)
	{
		BYTE* gateway = (BYTE*)VirtualAlloc(0, length, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE); // Allocate memory for our "gateway" or actual trampoline function
		memcpy_s(gateway, length, addresstoHook, length); // sets the bytes of the start address its gonna steal in the trampoline function before it steals them

		uintptr_t jmpBackAddress = addresstoHook - gateway - 5; // find the jump back address back to the originaladdress of the function were hooking
		*(gateway + length) = 0xE9; // we set a jmp instruction, after our stolen bytes by doing +length

		*(uintptr_t*)((uintptr_t)gateway + length + 1) = (DWORD)jmpBackAddress; // adding the jump back address to the jmp instruction

		Detour(hookfunction, addresstoHook, length); // Detour will set the 1st jump at the original address, than after its executed it will call the trampoline hook.

		return gateway; // we will return the trampoline function, so our hookfunction can call it
	}
	else
	{
		return 0;
	}
}

Hook::Hook(BYTE* Function, BYTE* Address, BYTE* ptr2_gateway, uintptr_t length) // function hooking, function to hook, gateway ptr, length
{
	this->hook_function = Function;
	this->original_function = Address;
	this->ptr_2_gateway_ptr = ptr2_gateway;
	this->length = length;
}

Hook::Hook(BYTE* Function, const char* moduleName, const char* exportName, BYTE* ptr2_gateway, uintptr_t length)
{
	HMODULE module = GetModuleHandle((LPCWSTR)moduleName);
	this->original_function = (BYTE*)GetProcAddress(module, exportName);
	this->hook_function = Function;
	this->length = length;
	this->ptr_2_gateway_ptr = ptr2_gateway;
}

void Hook::Enable()
{
	memcpy(originalBytes, original_function, length);
	*(uintptr_t*)ptr_2_gateway_ptr = (uintptr_t)Trampoline_Hook(original_function, hook_function, length);
	status = true;
}
void Hook::Disable()
{
	mem::Patch(original_function, originalBytes, length);
	status = false;
}
void Hook::Toggle()
{
	status ? Disable() : Enable();
}







void __fastcall hooked_shootFunc(DWORD* This, void* _EDX, vec_3& endPoint)
{
	endPoint.x = getClosestHeadPos().x;
	endPoint.y = getClosestHeadPos().y;
	endPoint.z = getClosestHeadPos().z;

	original_shootFunc(This, endPoint);
}
