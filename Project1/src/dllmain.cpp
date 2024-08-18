
#include<windows.h>
#include<iostream>
#include<vector>
#include <GL/GL.h>
#include <tchar.h>


#include"Beautify.h"
#include"Offsets.h"
#include"Structs.h"
#include"Cheats.h"
#include"Math.h"
#include"Hook.h"
#include"glDraw.h"

#include "opengl_hook.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl3.h"



DWORD WINAPI mainThread(HMODULE module)
{
	
	// Console Initialisation
	AllocConsole();
	FILE* fStream;
	freopen_s(&fStream, "CONOUT$", "w", stdout);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	btfy::titlepage();



	swapBuffer = Hook((BYTE*)hooked_wglSwapBuffers, (BYTE*)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers"), (BYTE*)&original_wglSwapBuffers, 5);
	silentaim_hook = Hook((BYTE*)hooked_shootFunc, (BYTE*)0x4c7200, (BYTE*)&original_shootFunc, 10);
	
	// Module Declaration
	//clientbaseAddr = (uintptr_t)GetModuleHandle(L"ac_client.exe");

	// Intialize static stuff
	//Debugging
	{
		std::cout << std::hex;
		//std::cout << addresses::entityList;
		std::cout << std::dec;
		std::cout << "\ntest: \n";
		std::cout << values::local_player->health;

		
	}
	

	
	
	swapBuffer.Enable();
	silentaim_hook.Enable();
	// Main dll loop

	while (!GetAsyncKeyState(VK_END))
	{ 
		Sleep(30);
	}

	swapBuffer.Disable();
	silentaim_hook.Disable();
																			//mem::Patch((BYTE*)addresses::shoot_function_hook_address, shoot_function_patch_opcode, 7);
	SetWindowLongPtr(GameWindow, GWLP_WNDPROC, (LONG_PTR)original_WndProc);
	// Exiting Thread
	if (fStream)
		fclose(fStream);

	FreeConsole();
	FreeLibraryAndExitThread(module, NULL);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD reasonforCall,LPVOID reserved) 
{
	switch (reasonforCall)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)mainThread, hmodule, 0, nullptr);
		DisableThreadLibraryCalls(hmodule);


	case DLL_THREAD_ATTACH:

	case DLL_THREAD_DETACH:


	case DLL_PROCESS_DETACH:
	default:
		break;
	}
	return 1;
}


int closest_entity_index;


void Cheats::silent_aim(Hook &h)
{
	int count = 0;
	float maxDist = (float)0xfffff;
	std::string name;
	
	vec2 middleScreen(wWidth / 2, wHeight / 2);


	for (int i = 0; i < (values::player_count - 1); i++)
	{
		vec2 screenPosition(0, 0);
		float Dist;
		if ((values::entity_list->ent[i] != 0) && (values::entity_list->ent[i]->health > 0) && (values::entity_list->ent[i]->team != values::local_player->team))
		{
			viewMatrix vm = *(viewMatrix*)(clientbaseAddr + 0x17DFFC - 0x2C);

			if (Math::worldToScreen(shuffle_vec(values::entity_list->ent[i]->head_position), screenPosition, vm, wWidth, wHeight)) {
				Dist = Math::Magnitude(middleScreen, screenPosition);
				if (Dist < maxDist)
				{
					maxDist = Dist;
					closest_head_pos_3d = values::entity_list->ent[i]->head_position;
					name = values::entity_list->ent[i]->name;
					closest_entity_index = i;
				}
			}
		}
	}

	if (values::player_count > 1)
	{
		
		std::cout << name << "\n";
		std::cout << maxDist << "\n";
	}
	else
	{
		
												//mem::Patch((BYTE*)addresses::shoot_function_hook_address, shoot_function_patch_opcode, 7);
	}

}

void Cheats::tracers()
{
	for (int i = 0; i < (values::player_count - 1); i++)
	{
		vec2 screenPosition(0, 0);
		float Dist;
		if ((values::entity_list->ent[i] != 0) && (values::entity_list->ent[i]->health > 0) && (values::entity_list->ent[i]->team != values::local_player->team))
		{
			viewMatrix vm = *(viewMatrix*)(clientbaseAddr + 0x17DFFC - 0x2C);

			if (Math::worldToScreen(shuffle_vec(values::entity_list->ent[i]->head_position), screenPosition, vm, wWidth, wHeight)) {
				if (i == closest_entity_index) {
					Gl::draw_line(vec2(wWidth / 2, 0), screenPosition, 0.5, rgb_colors::green);
				}
				else
				{
					Gl::draw_line(vec2(wWidth / 2, 0), screenPosition, 0.5, rgb_colors::purple);
				}
			}
		}
	}
}












// Old Code


/* BYTE* shoot_function_patch_opcode = (BYTE*)"\xF3\x0F\x7E\x00\x8B\x40\x08"; */



/* Old Trampoline Hook method
std::cout << std::hex;
original_wglSwapBuffers = (template_wglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
std::cout << (UINT)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers") << " dbg1\n";
original_wglSwapBuffers = (template_wglSwapBuffers)(Trampoline_Hook((BYTE*)original_wglSwapBuffers, (BYTE*)hooked_wglSwapBuffers, 5)); // we set the original function to trampoline
std::cout << (UINT) original_wglSwapBuffers << " dbg4\n";
*/

/*


__declspec (naked) void SilentAim()
{
	_asm
	{
		push ebx
		mov ebx, closest_head_pos_3d.x
		mov dword ptr[eax], ebx
		mov ebx, closest_head_pos_3d.z
		mov dword ptr[eax + 4], ebx
		mov ebx, closest_head_pos_3d.y
		mov dword ptr[eax + 8], ebx

		movq xmm0, qword ptr[eax]
		mov eax, [eax + 8]
		pop ebx
		jmp[values::silent_aim_jmp_back_address]
	}
}




*/