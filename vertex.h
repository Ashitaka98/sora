#pragma once
#include<glm/glm.hpp>
namespace sora {
	using namespace glm;
	class Vertex {
	public:
		Vertex();
		Vertex(const vec4& coordinate, const vec3& normal, const vec3& color, const vec2& textureCoordinate);
		
	public:
		vec4 _coordinate;
		vec3 _normal;
		vec3 _color;
		vec4 _clippingCoordinate;
		vec4 _viewportCoordinate;
		vec2 _textureCoordinate;
	};
	
}
