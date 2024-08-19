#include "opengl_hook.h"

void RenderMain()
{
	ImGui::Begin("Window Title");
	ImGui::Text("Hello world!");
	ImGui::End();
}


BOOL __stdcall hooked_wglSwapBuffers(HDC hdc)
{


	//std::cout << "Hooked";
	InitOpenGL3(hdc,&imgui_initialized);
	RenderOpenGL3(handle_GL_rendering_context, hdc, RenderMain);

	values::player_count = *(DWORD*)(0x58AC0C);
	addresses::entityList = *(DWORD*)(clientbaseAddr + 0x18AC04);

	Gl::setup_ortho();
	GetWindowRect(gameExtGameWindow, &WindowSize);

	wWidth = WindowSize.right - WindowSize.left;
	wHeight = WindowSize.bottom - WindowSize.top;

	if (values::old_player_count_buffer != values::player_count)
	{
		//Detour((BYTE*)SilentAim, (BYTE*)addresses::shoot_function_hook_address, 7);

		std::cout << "player_count changed\n";
		values::entity_list = (__temporary::entlist*)(addresses::entityList);
		std::cout << values::entity_list->ent[0]->name << " is player\n";

	}
	values::old_player_count_buffer = values::player_count;

	Cheats::tracers();
	Cheats::silent_aim();

	Gl::draw_frame(200, 200, 300, 300, 2, rgb_colors::red);
	vec_2 fss(200, 200);
	vec_2 tss(200 + 300, 200 + 300);

	Gl::draw_line(fss, tss, 2, rgb_colors::red);

	
	
	Gl::restore_gl();



	// our function needs to call the trampoline function, so it can jump back to the  original address, which is why we call original
	return original_wglSwapBuffers(hdc); // If our function has void as its return type and not smt like BOOL, we dont need  to use return
};


void InitOpenGL3(HDC hdc, bool* initialised)
{
	if (WindowFromDC(hdc) == GameWindow && *initialised) return;
	auto tStatus = true;

	GameWindow = WindowFromDC(hdc);
	auto wLPTR = SetWindowLongPtr(GameWindow, GWLP_WNDPROC, (LONG_PTR) hook_WndProc);

	if (*initialised)
	{
		ImGui_ImplWin32_Init(GameWindow);
		ImGui_ImplOpenGL3_Init();
		return;
	}

	if (!wLPTR) return;

	original_WndProc = (WNDPROC) wLPTR;
	handle_GL_rendering_context = wglCreateContext(hdc);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	tStatus &= ImGui_ImplWin32_Init(GameWindow);
	tStatus &= ImGui_ImplOpenGL3_Init();

	*initialised = true;
}

LRESULT CALLBACK hook_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	return CallWindowProc(original_WndProc, hwnd, msg, wparam, lparam);
}


void RenderOpenGL3(HGLRC WglContext, HDC hDc, void callback())
{

	auto o_WglContext = wglGetCurrentContext();
	wglMakeCurrent(hDc, WglContext);
	ImGui_ImplOpenGL3_NewFrame();

	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	callback();

	ImGui::EndFrame();
	ImGui::Render();

	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	wglMakeCurrent(hDc, o_WglContext);

}