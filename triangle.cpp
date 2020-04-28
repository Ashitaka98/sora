#include"triangle.h"

Triangle::Triangle(){
	a = glm::vec4(1, 0, 0, 1);
	b = glm::vec4(-1, 0, 0, 1);
	c = glm::vec4(0, 1, 0, 1);
	
	color_a = glm::vec3(255, 0, 0);	//blue
	color_b = glm::vec3(0, 255, 0);	//green
	color_c = glm::vec3(0, 0, 255);	//red
	
	p_object_coordinate_frame = nullptr;
	p_object_frame_inv = nullptr;
}
