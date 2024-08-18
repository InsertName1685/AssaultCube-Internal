#include "Cheats.h"
#include<iostream>


void mem::Patch( BYTE* address, BYTE* code, UINT size)
{
	DWORD oldprotect;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(address, code, size);
	VirtualProtect(address, size, oldprotect, &oldprotect);
}

void mem::Nop( BYTE* address, UINT size)
{
	BYTE* noparray = new BYTE[size];
	memset(noparray, 0x90, size);
	mem::Patch(address, noparray, size);
	delete[] noparray;
}

