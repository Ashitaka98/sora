#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


//----------------------------------------------Projections------------------------------------------------------------

// return matrix used for transforming camera coordinate to clipping coordinate, field of view should be in radians
inline glm::mat4 matrix_PerspectiveProjection(const float theta, const float aspect_ratio, const glm::vec2& shift, const float near, const float far) {
    glm::mat4 perspective_matrix = glm::perspective(theta, aspect_ratio, near, far);
    glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-shift.x, -shift.y, 0));
    return translate_matrix * perspective_matrix;
}

// return matrix used for transforming clipping coordinate to window coordinate
inline glm::mat4 matrix_viewportTransform(const int width, const int height) {
    glm::mat4 viewport_matrix(
        width / 2, 0, 0, 0,
        0, height / 2, 0, 0,
        0, 0, 0.5, 0,
        (width - 1) / 2, (height - 1) / 2, 0.5, 1
    );
    return viewport_matrix;
}

