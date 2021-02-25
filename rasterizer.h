#pragma once
#include<glm/glm.hpp>
#include"vertex.h"
#include"triangle.h"
#include<vector>
#include<memory>
#include<functional>
namespace sora {
	using namespace glm;
	using namespace std;
	class Rasterizer {
		typedef function<void(int X, int Y, int textCoorU, int textCoorV, float illuminant)> callback;
	public:
		Rasterizer(const shared_ptr<vector<Vertex>> &pVertice, const shared_ptr<vector<Triangle>> &pTris, const mat4 &cameraCoordinateFrame, const mat4& objectCoordinateFrame, const uint16 width, const uint16 height,callback writeColorBufferCallback);
		void rasterize();
		void setCameraFrame(const mat4& cameraCoordinateFrame);
	private:
		// camera and object
		shared_ptr<vector<Vertex>> _pVertice;
		shared_ptr<vector<Triangle>> _pTris;
		mat4 _cameraCoordinateFrame;
		mat4 _cameraFrameInv;
		mat4 _objectCoordinateFrame;
		mat4 _objectFrameInv;


		// scene illuminant 
		float _radianceAmbient;					// ambient light
		float _radianceDirectional;				// directional light
		vec3 _directionDirectional;				// direction of the directional light, which is a unit vector given in world coordinate frame 

		// window size
		uint16 _width;
		uint16 _height;

		// buffer
		unique_ptr<float[]> _zBuffer;	// transparent to programmer

		// write color buffer callback
		callback _writeColorBuffer;
	};
}