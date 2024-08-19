#pragma once

#include<Windows.h>
#include"Structs.h"


static uintptr_t clientbaseAddr = (uintptr_t)GetModuleHandle(L"ac_client.exe");


namespace addresses
{
	static uintptr_t entityList;
	static DWORD shoot_function_hook_address = (clientbaseAddr + 0xC7363);;
}

namespace values
{
	Entity* local_player = (Entity*)*(DWORD*)(clientbaseAddr + 0x17E0A8);
	DWORD silent_aim_jmp_back_address = addresses::shoot_function_hook_address + 7;
	vec_3 closest_head_position;
	int player_count;
	int old_player_count_buffer = 0;
	__temporary::entlist* entity_list;
	
	
}

static vec_3 closest_head_pos_3d;