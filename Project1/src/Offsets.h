#pragma once

#include<Windows.h>
#include"Structs.h"


static uintptr_t clientbaseAddr = (uintptr_t)GetModuleHandle(L"ac_client.exe");;


namespace addresses
{
	static uintptr_t entityList;
	static DWORD shoot_function_hook_address = (clientbaseAddr + 0xC7363);;
}

namespace values
{
	static Entity* local_player = (Entity*)*(DWORD*)(clientbaseAddr + 0x17E0A8);
	static DWORD silent_aim_jmp_back_address = addresses::shoot_function_hook_address + 7;
	static vec3 closest_head_position;
	static int player_count;
	static int old_player_count_buffer = 0;
	static __temporary::entlist* entity_list;
	
	
}

static vec3 closest_head_pos_3d;