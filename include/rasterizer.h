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
		Rasterizer(uint32 width, uint32 height):mViewportWidth(width), mViewportHeight(height) {
			mZBuffer.resize(width * height);
		}

		inline std::shared_ptr<Camera> GetCamera() { return mCamera; }

		inline void SetAmbientRadiance(float radiance) { mAmbientRadiance = radiance; }
		inline void SetIlluminare(std::shared_ptr<Illuminare> light) { mLight = light; }
		inline void SetCamera(std::shared_ptr<Camera> camera) { mCamera=camera; }
		inline void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		inline void SetObjectCoordFrame(const mat4& objectFrame) { 
			mObjectCoordFrame = objectFrame; 
			mObjectFrameInv = glm::inverse(objectFrame); 
		}

		inline void SetData(uint8* vb, uint32 vbsize, uint8* ib, uint32 ibsize, uint32 primitive, VertexStreamLayout layout) {
			mVertexBuffer = vb;
			vbSize = vbsize;
			mIndexBuffer = ib;
			ibSize = ibsize; 
			primitiveNum = primitive;
			mLayout = layout;
		}

		inline void SetWriter(FrameBufferWriter writer) { mWriter = writer; }

		inline void EnableAmbient(bool enable) { mUseAmbient = enable; }
		inline void EnableShadow(bool enable) { mCastShadow = enable; }

		// phong shading
		void Rasterize();

		inline void ClearDepthBuffer() {
			// clear z-buffer
			for (uint32 i = 0; i < mViewportWidth * mViewportHeight; i++)
				mZBuffer[i] = 1;
		}
	private:
		uint8* mVertexBuffer{nullptr};
		uint8* mIndexBuffer{nullptr};
		VertexStreamLayout mLayout{};
		uint32 vbSize{ 0 };
		uint32 ibSize{ 0 };
		uint32 primitiveNum{ 0 };

		mat4 mObjectCoordFrame{};
		mat4 mObjectFrameInv{};

		ProjectionType mProjType{ ProjectionType::Perspective };

		std::shared_ptr<Camera> mCamera{};
		std::shared_ptr<Texture> mTexture{};
		std::shared_ptr<Illuminare> mLight{};

		bool mUseAmbient{ true };
		bool mCastShadow{ true };
		bool mDepthTest{ true };
		bool mDepthWrite{ true };
		float mAmbientRadiance{ 0 };

		// window size
		uint16 mViewportWidth{ 0 };
		uint16 mViewportHeight{ 0 };

		std::vector<float> mZBuffer;	
		FrameBufferWriter mWriter;
	};
}