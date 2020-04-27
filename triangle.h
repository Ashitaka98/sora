#pragma once
#include<glm/glm.hpp>

// camera coordinate frame transformation_matrix with respect to world coordinate
extern glm::mat4 camera_coordinate_frame;
extern glm::mat4 camera_frame_inv;

class Triangle {
public:
	// constructors
	Triangle();
	Triangle(const glm::vec4& a, const glm::vec4& b, const glm::vec4& c, const glm::vec3& color_A, const glm::vec3& color_B, const glm::vec3& color_C, const glm::mat4& obj_frame);

	// coordinate conversion between obj, cam, world coordinate frames
	Triangle obj2world();
	Triangle world2obj();
	Triangle world2cam();
	Triangle cam2world();

	// coordinates of three vertexes of this triangle
	glm::vec4 a;
	glm::vec4 b;
	glm::vec4 c;
	// colors of three vertexes of this triangle
	glm::vec3 color_a;
	glm::vec3 color_b;
	glm::vec3 color_c;
	// object coordinate frame transformation_matrix with respect to world coordinate
	glm::mat4 object_coordinate_frame;
	glm::mat4 object_frame_inv;
};

//-----------------coordinate conversion between obj, cam, world coordinate frames-------------------------------------

inline Triangle Triangle::obj2world() {
	Triangle ret(*this);
	ret.a = object_coordinate_frame * a;
	ret.b = object_coordinate_frame * b;
	ret.c = object_coordinate_frame * c;
	return ret;
}

inline Triangle Triangle::world2obj() {
	Triangle ret(*this);
	ret.a = object_frame_inv * a;
	ret.b = object_frame_inv * b;
	ret.c = object_frame_inv * c;
	return ret;
}

inline Triangle Triangle::cam2world() {
	Triangle ret(*this);
	ret.a = camera_coordinate_frame * a;
	ret.b = camera_coordinate_frame * b;
	ret.c = camera_coordinate_frame * c;
	return ret;
}

inline Triangle Triangle::world2cam() {
	Triangle ret(*this);
	ret.a = camera_frame_inv * a;
	ret.b = camera_frame_inv * b;
	ret.c = camera_frame_inv * c;
	return ret;
}

//---------------------------------------------------------------------------------------------------------------------
