#pragma once

#include <Windows.h>
#include <functional> 
#include <GL/gl.h>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl3.h"


#include "Offsets.h"
#include "glDraw.h"
#include "Hook.h"
#include "Cheats.h"
typedef BOOL(__stdcall* template_wglSwapBuffers)(HDC hdc);
//typedef LRESULT(CALLBACK* WNDPROC) (HWND   hwnd, UINT   uMsg, WPARAM wParam, LPARAM lParam);


template_wglSwapBuffers original_wglSwapBuffers; // This will be the original function, we will make it point to the original function like a struct

BOOL __stdcall hooked_wglSwapBuffers(HDC hdc);


static RECT WindowSize;
static HWND GameWindow = FindWindowA(NULL, (LPCSTR)"AssaultCube");
static HWND gameExtGameWindow = FindWindowA(NULL, (LPCSTR)"AssaultCube");
static int wWidth;
static int wHeight;


void InitOpenGL3(HDC hDc, bool* init);
void RenderOpenGL3(HGLRC WglContext, HDC hDc, void callback());
bool imgui_initialized = false;

HGLRC handle_GL_rendering_context;

WNDPROC	original_WndProc;
LRESULT CALLBACK hook_WndProc(HWND hwnd,UINT msg, WPARAM wparam, LPARAM lparam);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);