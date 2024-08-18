#pragma once
#include <Windows.h>
#include"Structs.h"
#include "Hook.h"
namespace mem
{
	void Patch(BYTE* address, BYTE* code, UINT size);
	void Nop(BYTE* address, UINT size);
};

namespace Cheats
{
	void bhop();
	void box_esp();
	void tracers();
	void bullet_tracers();
	void silent_aim(struct Hook& h);
};

