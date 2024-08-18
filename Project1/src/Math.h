#pragma once

#include "Structs.h"
#include<vector>

namespace Math
{
	bool worldToScreen(vec3 pos, vec2& screen, viewMatrix matrix, int windowWidth, int windowHeight);

	bool lookAt(vec3 cameraPos, vec3 target, vec2& rotation);

	float Magnitude(vec2 from, vec2 to);
	float Magnitude3(vec3 from, vec3 to);
};

