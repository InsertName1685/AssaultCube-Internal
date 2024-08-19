#include "Cheats.h"
#include<iostream>

vec_3 closestHeadPosition;

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

int closest_entity_index;


void Cheats::silent_aim()
{
	clientbaseAddr = (uintptr_t)GetModuleHandle(L"ac_client.exe");
	addresses::entityList = *(DWORD*)(clientbaseAddr + 0x18AC04);
	int count = 0;
	float maxDist = (float)0xfffff;
	std::string name;
	GetWindowRect(FindWindowA(NULL, "AssaultCube"), &WindowSize);
	wWidth = WindowSize.right - WindowSize.left;
	wHeight = WindowSize.bottom - WindowSize.top;

	vec_2 middleScreen(wWidth / 2, wHeight / 2);

	
	for (int i = 0; i < (values::player_count - 1); i++)
	{
		values::entity_list = (__temporary::entlist*)addresses::entityList;
		std::cout << values::entity_list << "\n";
		std::cout << values::entity_list->ent << "\n";

		vec_2 screenPosition(0, 0);
		float Dist;
		if ((values::entity_list != nullptr) && (values::entity_list->ent[i] != 0) && (values::entity_list->ent[i]->health > 0) && (values::entity_list->ent[i]->team != values::local_player->team))
		{
			viewMatrix vm = *(viewMatrix*)(clientbaseAddr + 0x17DFFC - 0x2C);

			if (Math::worldToScreen(shuffle_vec(values::entity_list->ent[i]->head_position), screenPosition, vm, wWidth, wHeight)) {
				Dist = Math::Magnitude(middleScreen, screenPosition);
				if (Dist < maxDist)
				{
					maxDist = Dist;
					closestHeadPosition = values::entity_list->ent[i]->head_position;
					name = values::entity_list->ent[i]->name;
					closest_entity_index = i;
				}
			}
		}
	}

	if (values::player_count > 1)
	{
		std::cout << name << "\n";
		//std::cout << maxDist << "\n";
		std::cout << closestHeadPosition.x << ", " << closestHeadPosition.y << ", " << closestHeadPosition.z << "\n";
	}
	else
	{

		//mem::Patch((BYTE*)addresses::shoot_function_hook_address, shoot_function_patch_opcode, 7);
	}

}

void Cheats::tracers()
{
	clientbaseAddr = (uintptr_t)GetModuleHandle(L"ac_client.exe");
	addresses::entityList = *(DWORD*)(clientbaseAddr + 0x18AC04);
	for (int i = 0; i < (values::player_count - 1); i++)
	{
		vec_2 screenPosition(0, 0);
		float Dist;
		if ((values::entity_list != nullptr) && (values::entity_list->ent[i] != nullptr) && (values::entity_list->ent[i]->health > 0) && (values::entity_list->ent[i]->team != values::local_player->team))
		{
			viewMatrix vm = *(viewMatrix*)(clientbaseAddr + 0x17DFFC - 0x2C);

			if (Math::worldToScreen(shuffle_vec(values::entity_list->ent[i]->head_position), screenPosition, vm, wWidth, wHeight)) {
				if (i == closest_entity_index) {
					//std::cout << "Screen Position: " << screenPosition.x << ", " << screenPosition.y << "\n";
					//std::cout << "Screen Size: " << wWidth << ", " << wHeight << "\n";
					Gl::draw_line(vec_2(wWidth / 2, 0), screenPosition, 0.5, rgb_colors::green);
				}
				else
				{
					Gl::draw_line(vec_2(wWidth / 2, 0), screenPosition, 0.5, rgb_colors::purple);
				}
			}
		}
	}
}


vec_3 getClosestHeadPos() {
	return closestHeadPosition;
}