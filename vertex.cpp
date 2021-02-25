#include"vertex.h"
namespace sora {
	Vertex::Vertex() {

	}
	Vertex::Vertex(const vec4& coordinate, const vec3& normal, const vec3& color, const vec2& textureCoordinate) {
		_coordinate = coordinate;
		_normal = normal;
		_color = color;
		_textureCoordinate = textureCoordinate;
	}
}