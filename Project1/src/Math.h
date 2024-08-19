#pragma once

#include "Structs.h"
#include<vector>

namespace Math
{
	bool worldToScreen(vec_3 pos, vec_2& screen, viewMatrix matrix, int windowWidth, int windowHeight);

	bool lookAt(vec_3 cameraPos, vec_3 target, vec_2& rotation);

	float Magnitude(vec_2 from, vec_2 to);
	float Magnitude3(vec_3 from, vec_3 to);
};

