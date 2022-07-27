#pragma once
#include<glm/gtc/matrix_transform.hpp>

#include"defines.h"

namespace sora {
    //----------------------------------------------Projections------------------------------------------------------------
	// return matrix used for transforming camera coordinate to clipping coordinate, field of view should be in radians
    inline mat4 MatrixPerspectiveProjection(const float theta, const float aspectRatio, const vec2& shift, const float near, const float far) {
        mat4 perspectiveMatrix = glm::perspective(theta, aspectRatio, near, far);
        mat4 translateMatrix = glm::translate(mat4(1.0f), vec3(-shift.x, -shift.y, 0));
        return translateMatrix * perspectiveMatrix;
    }

	inline mat4 MatrixOrthogonalProjection(const float left, const float right, const float bottom, const float top, const float near, const float far) {
		return glm::ortho(left, right, bottom, top, near, far);
	}

    // return matrix used for transforming clipping coordinate to window coordinate
    inline mat4 MatrixViewportTransform(const int width, const int height) {
        mat4 viewportMatrix(
            width / 2, 0, 0, 0,
            0, height / 2, 0, 0,
            0, 0, 0.5, 0,
            (width - 1) / 2, (height - 1) / 2, 0.5, 1
        );
        return viewportMatrix;
    }
	inline vec3 BarycentricCoordinate(const vec2& A, const vec2& B, const vec2& C, const vec2& point) {
		float u, v, w;
		vec3 v1 = vec3(B.x - A.x, C.x - A.x, point.x - A.x);
		vec3 v2 = vec3(B.y - A.y, C.y - A.y, point.y - A.y);
		vec3 cross_product = glm::cross(v1, v2);
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
		return vec3{ w, u, v };
	}
} 