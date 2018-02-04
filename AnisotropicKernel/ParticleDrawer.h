#pragma once

#include <GLFW\glfw3.h>
#include <vector>

#include "Vector2f.h"

class ParticleDrawer {
public:
	static void dot(std::vector<Vector2f>& vertices, float radius);
	static void circle(std::vector<Vector2f>& vertices, float radius, int resolution);
	static void transformed_circle(std::vector<Matrix2f>& matrices, std::vector<Vector2f>& vertices, float radius, int resolution);
};