#pragma once
#include<glm/glm.hpp>

namespace sora {
	using namespace glm;
	class Triangle {
	public:
		Triangle(const int A, const int B, const int C);
	public:
		// element index
		int _A;
		int _B;
		int _C;
	};
}
