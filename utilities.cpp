#include"utilities.h"
glm::vec3 barycentric_coordinate(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, const glm::vec2& point) {
	float u, v, w;
	glm::vec3 v1 = glm::vec3(B.x - A.x, C.x - A.x, point.x - A.x);
	glm::vec3 v2 = glm::vec3(B.y - A.y, C.y - A.y, point.y - A.y);
	glm::vec3 cross_product = glm::cross(v1, v2);
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
	return glm::vec3(w, u, v);
}