#include"utilities.h"
namespace sora {
	vec3 barycentric_coordinate(const vec2& A, const vec2& B, const vec2& C, const vec2& point) {
		float u, v, w;
		vec3 v1 = vec3(B.x - A.x, C.x - A.x, point.x - A.x);
		vec3 v2 = vec3(B.y - A.y, C.y - A.y, point.y - A.y);
		vec3 cross_product = cross(v1, v2);
		if (abs(cross_product.z) < 0.001)
		{
			u = 0;
			v = 0;
			w = 1;
		}
		else {
			u = cross_product.x / -cross_product.z;
			v = cross_product.y / -cross_product.z;
			w = 1 - u - v;
		}
		return vec3(w, u, v);
	}
}