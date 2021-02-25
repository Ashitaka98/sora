#pragma once
#include<memory>
#include<vector>
#include<string>
#include"vertex.h"
#include"triangle.h"
namespace sora {
	using namespace std;
	// Cube is a demo geometry
	class Cube {
	private:
		Cube();
	public:
		static const int _width=512;
		static const int _height=512;
		static Cube getInstance();
		static string getTexturePath();
	public:
		shared_ptr<vector<Vertex>> _vertice;
		shared_ptr<vector<Triangle>> _tris;
	};
}