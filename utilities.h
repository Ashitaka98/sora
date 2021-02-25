#pragma once
#include"triangle.h"
#include<glm/gtc/matrix_transform.hpp>

namespace sora {
	using namespace glm;
    //----------------------------------------------Projections------------------------------------------------------------

// return matrix used for transforming camera coordinate to clipping coordinate, field of view should be in radians
    inline mat4 matrixPerspectiveProjection(const float theta, const float aspectRatio, const vec2& shift, const float near, const float far) {
        mat4 perspectiveMatrix = perspective(theta, aspectRatio, near, far);
        mat4 translateMatrix = translate(mat4(1.0f), vec3(-shift.x, -shift.y, 0));
        return translateMatrix * perspectiveMatrix;
    }

    // return matrix used for transforming clipping coordinate to window coordinate
    inline mat4 matrixViewportTransform(const int width, const int height) {
        mat4 viewportMatrix(
            width / 2, 0, 0, 0,
            0, height / 2, 0, 0,
            0, 0, 0.5, 0,
            (width - 1) / 2, (height - 1) / 2, 0.5, 1
        );
        return viewportMatrix;
    }
	vec3 barycentric_coordinate(const vec2& A, const vec2& B, const vec2& C, const vec2& point);
} 