#pragma once

#include <algorithm>
#include <vector>
#include "Matrix2f.h"
#include "Vector2f.h"
#include "SimConstants.h"

namespace SurfaceReconstruction {

	class AnisotropicKernel {
	public:
		static std::vector<Matrix2f> calc(const std::vector<Vector2f>& particles, std::vector<Vector2f>& new_pos);
	};

}

