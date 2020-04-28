#pragma once
#include<glm/glm.hpp>

// camera coordinate frame transformation_matrix with respect to world coordinate
extern glm::mat4 camera_coordinate_frame;
extern glm::mat4 camera_frame_inv;

class Triangle {
public:
	// constructors
	Triangle();

	// coordinate conversion between obj, cam, world coordinate frames
	Triangle obj2world();
	Triangle world2obj();
	Triangle world2cam();
	Triangle cam2world();


	// coordinates of three vertexes of this triangle, may be in any coordinate frame
	glm::vec4 a;
	glm::vec4 b;
	glm::vec4 c;
	// colors of three vertexes, when texture is introduced, these should be commented out
	/*glm::vec3 color_a;
	glm::vec3 color_b;
	glm::vec3 color_c;*/
	// normals of three vertexes in object coordinate frame, the fourth coordinate should always be zero, use vec4 just for convenience
	glm::vec4 normal_a;
	glm::vec4 normal_b;
	glm::vec4 normal_c;
	// texture coordinate of three vertexes
	glm::vec2 tex_coord_a;
	glm::vec2 tex_coord_b;
	glm::vec2 tex_coord_c;

	// pointer object coordinate frame transformation_matrix with respect to world coordinate, which may be shared by many triangles
	glm::mat4 *p_object_coordinate_frame;
	glm::mat4 *p_object_frame_inv;
};

//-----------------coordinate conversion between obj, cam, world coordinate frames-------------------------------------

inline Triangle Triangle::obj2world() {
	Triangle ret;
	ret.a = *p_object_coordinate_frame * a;
	ret.b = *p_object_coordinate_frame * b;
	ret.c = *p_object_coordinate_frame * c;
	return ret;
}

inline Triangle Triangle::world2obj() {
	Triangle ret;
	ret.a = *p_object_frame_inv * a;
	ret.b = *p_object_frame_inv * b;
	ret.c = *p_object_frame_inv * c;
	return ret;
}

inline Triangle Triangle::cam2world() {
	Triangle ret;
	ret.a = camera_coordinate_frame * a;
	ret.b = camera_coordinate_frame * b;
	ret.c = camera_coordinate_frame * c;
	return ret;
}

inline Triangle Triangle::world2cam() {
	Triangle ret;
	ret.a = camera_frame_inv * a;
	ret.b = camera_frame_inv * b;
	ret.c = camera_frame_inv * c;
	return ret;
}

//---------------------------------------------------------------------------------------------------------------------
