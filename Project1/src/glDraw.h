#pragma once
#pragma comment(lib, "OpenGl32.lib")

#include<Windows.h>
#include<stdio.h>
#include<gl/GL.h>

#include"Cheats.h"

namespace rgb_colors
{
	static GLubyte red[3] = { 255,0,0 };
	static GLubyte blue[3] = { 0,0,255 };
	static GLubyte green[3] = { 0,255,0 };
	static GLubyte black[3] = { 255,255,255 };
	static GLubyte white[3] = { 255,255,255 };
	static GLubyte purple[3] = { 255, 0, 255 };
	static GLubyte gray[3] = { 55,55,55 };
}

namespace Gl
{
	void setup_ortho();
	void restore_gl();
	void draw_filled_box(float x, float y, float width, float height, GLubyte color[3]);
	void draw_frame(float x, float y, float width, float height,float outline_width, GLubyte color[3]);
	void draw_line(vec_2 from, vec_2  to, float width, GLubyte color[3]);
}

