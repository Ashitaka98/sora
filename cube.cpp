#include"cube.h"
namespace sora {
    Cube::Cube(){
    }
    // we intend to implement flat shading, so we duplicate each vertex of the cube since we want coherent normal within a triangle's vertice
	Cube Cube::getInstance() {
        Cube cube;
        cube._vertice = make_shared<vector<Vertex>>();
        cube._tris = make_shared<vector<Triangle>>();
        cube._vertice->push_back(Vertex(
            vec4(-1, 1, 1, 1),
            vec4(0, 0, 1, 0),
            vec3(),
            vec2(0, 0)
            ));
        cube._vertice->push_back(Vertex(
            vec4(1, 1, 1, 1),
            vec4(0, 0, 1, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, -1, 1, 1),
            vec4(0, 0, 1, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._tris->push_back(Triangle(0, 1, 2));

        cube._vertice->push_back(Vertex(
            vec4(1, -1, 1, 1),
            vec4(0, 0, 1, 0),
            vec3(),
            vec2(511, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, -1, 1, 1),
            vec4(0, 0, 1, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, 1, 1, 1),
            vec4(0, 0, 1, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._tris->push_back(Triangle(3, 4, 5));

        cube._vertice->push_back(Vertex(
            vec4(1, -1, 1, 1),
            vec4(1, 0, 0, 0),
            vec3(),
            vec2(511, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, 1, 1, 1),
            vec4(1, 0, 0, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, -1, -1, 1),
            vec4(1, 0, 0, 0),
            vec3(),
            vec2(0, 511)
            ));
        cube._tris->push_back(Triangle(6, 7, 8));

        cube._vertice->push_back(Vertex(
            vec4(1, 1, -1, 1),
            vec4(1, 0, 0, 0),
            vec3(),
            vec2(0, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, -1, -1, 1),
            vec4(1, 0, 0, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, 1, 1, 1),
            vec4(1, 0, 0, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._tris->push_back(Triangle(9, 10, 11));

        cube._vertice->push_back(Vertex(
            vec4(1, 1, -1, 1),
            vec4(0, 0, -1, 0),
            vec3(),
            vec2(0, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, 1, -1, 1),
            vec4(0, 0, -1, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, -1, -1, 1),
            vec4(0, 0, -1, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._tris->push_back(Triangle(12, 13, 14));

        cube._vertice->push_back(Vertex(
            vec4(-1, -1, -1, 1),
            vec4(0, 0, -1, 0),
            vec3(),
            vec2(511, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, -1, -1, 1),
            vec4(0, 0, -1, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, 1, -1, 1),
            vec4(0, 0, -1, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._tris->push_back(Triangle(15, 16, 17));

        cube._vertice->push_back(Vertex(
            vec4(-1, -1, -1, 1),
            vec4(-1, 0, 0, 0),
            vec3(),
            vec2(511, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, 1, -1, 1),
            vec4(-1, 0, 0, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, -1, 1, 1),
            vec4(-1, 0, 0, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._tris->push_back(Triangle(18, 19, 20));

        cube._vertice->push_back(Vertex(
            vec4(-1, 1, 1, 1),
            vec4(-1, 0, 0, 0),
            vec3(),
            vec2(0, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, -1, 1, 1),
            vec4(-1, 0, 0, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, 1, -1, 1),
            vec4(-1, 0, 0, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._tris->push_back(Triangle(21, 22, 23));

        cube._vertice->push_back(Vertex(
            vec4(1, 1, -1, 1),
            vec4(0, 1, 0, 0),
            vec3(),
            vec2(511, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, 1, 1, 1),
            vec4(0, 1, 0, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, 1, -1, 1),
            vec4(0, 1, 0, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._tris->push_back(Triangle(24, 25, 26));

        cube._vertice->push_back(Vertex(
            vec4(-1, 1, 1, 1),
            vec4(0, 1, 0, 0),
            vec3(),
            vec2(0, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, 1, -1, 1),
            vec4(0, 1, 0, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, 1, 1, 1),
            vec4(0, 1, 0, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._tris->push_back(Triangle(27, 28, 29));

        cube._vertice->push_back(Vertex(
            vec4(1, -1, 1, 1),
            vec4(0, -1, 0, 0),
            vec3(),
            vec2(511, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, -1, -1, 1),
            vec4(0, -1, 0, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, -1, 1, 1),
            vec4(0, -1, 0, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._tris->push_back(Triangle(30, 31, 32));

        cube._vertice->push_back(Vertex(
            vec4(-1, -1, -1, 1),
            vec4(0, -1, 0, 0),
            vec3(),
            vec2(0, 0)
        ));
        cube._vertice->push_back(Vertex(
            vec4(-1, -1, 1, 1),
            vec4(0, -1, 0, 0),
            vec3(),
            vec2(0, 511)
        ));
        cube._vertice->push_back(Vertex(
            vec4(1, -1, -1, 1),
            vec4(0, -1, 0, 0),
            vec3(),
            vec2(511, 0)
        ));
        cube._tris->push_back(Triangle(33, 34, 35));
        return cube;
	}
   
    string Cube::getTexturePath() {
        return "../res/marbel.jpg";
    }
}