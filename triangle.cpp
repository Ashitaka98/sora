#include"triangle.h"

Triangle::Triangle(){
	a = glm::vec4(1, 0, 0, 1);
	b = glm::vec4(-1, 0, 0, 1);
	c = glm::vec4(0, 1, 0, 1);
	object_coordinate_frame = glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, -1, 1
	);
	color_a = glm::vec3(255, 0, 0);	//blue
	color_b = glm::vec3(0, 255, 0);	//green
	color_c = glm::vec3(0, 0, 255);	//red

	object_frame_inv = glm::inverse(object_coordinate_frame);
}
Triangle::Triangle(const glm::vec4& a, const glm::vec4& b, const glm::vec4& c, const glm::vec3& color_A, const glm::vec3& color_B, const glm::vec3& color_C, const glm::mat4& obj_frame) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->color_a = color_A;
	this->color_b = color_B;
	this->color_c = color_C;
	this->object_coordinate_frame = obj_frame;
	this->object_frame_inv = glm::inverse(obj_frame);
}