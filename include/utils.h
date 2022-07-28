#pragma once
#include<glm/gtc/matrix_transform.hpp>

#include"defines.h"

namespace sora {
    //----------------------------------------------Projections------------------------------------------------------------
	// return matrix used for transforming camera coordinate to clipping coordinate, field of view should be in radians
    inline mat4 MatrixPerspectiveProjection(const float theta, const float aspectRatio, const vec2& shift, const float zNear, const float zFar) {
        mat4 perspectiveMatrix = glm::perspective(theta, aspectRatio, zNear, zFar);
        mat4 translateMatrix = glm::translate(mat4(1.0f), vec3(-shift.x, -shift.y, 0));
        return translateMatrix * perspectiveMatrix;
    }

	inline mat4 MatrixOrthogonalProjection(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar) {
		return glm::ortho(left, right, bottom, top, zNear, zFar);
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
        vec2 v0 = B - A, v1 = C - A, v2 = point - A;
        float d00 = glm::dot(v0, v0);
        float d01 = glm::dot(v0, v1);
        float d11 = glm::dot(v1, v1);
        float d20 = glm::dot(v2, v0);
        float d21 = glm::dot(v2, v1);
        float denom = d00 * d11 - d01 * d01;
        float u, v, w;
        v = (d11 * d20 - d01 * d21) / denom;
        w = (d00 * d21 - d01 * d20) / denom;
        u = 1.0f - v - w;
        return { u,v,w };
	}
} 