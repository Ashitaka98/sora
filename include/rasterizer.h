#pragma once
#include <vector>
#include <memory>
#include <functional>

#include"defines.h"
#include "camera.h"
#include "illuminare.h"
#include "texture.h"
namespace sora {
	class Rasterizer {
		using FrameBufferWriter = std::function<void(int X,int Y, const ubvec3 &color)>;
	public:
		Rasterizer(uint32 width, uint32 height):mViewportWidth(width), mViewportHeight(height) {}

		inline void SetAmbientRadiance(float radiance) { mAmbientRadiance = radiance; }
		inline void SetIlluminare(std::shared_ptr<Illuminare> light) { mLight = light; }
		inline void SetCamera(std::shared_ptr<Camera> camera) { mCamera=camera; }
		inline void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		inline void SetObjectCoordFrame(const mat4& objectFrame) { 
			mObjectCoordFrame = objectFrame; 
			mObjectFrameInv = glm::inverse(objectFrame); 
		}

		inline void SetData(DrawCallData data) { mData = data; }

		// phong shading
		void Rasterize(FrameBufferWriter writer, std::vector<float> &zBuffer, std::vector<float>&shadowMap);

		friend class RenderController;
	private:
		DrawCallData mData;

		mat4 mObjectCoordFrame{};
		mat4 mObjectFrameInv{};

		std::shared_ptr<Camera> mCamera{};
		std::shared_ptr<Texture> mTexture{};
		std::shared_ptr<Illuminare> mLight{};

		bool mUseAmbient{ true };
		bool mCastShadow{ true };
		bool mDepthTest{ true };
		bool mDepthWrite{ true };
		bool mShading{ true };
		float mAmbientRadiance{ 0 };

		// window size
		uint16 mViewportWidth{ 0 };
		uint16 mViewportHeight{ 0 };
	};
}