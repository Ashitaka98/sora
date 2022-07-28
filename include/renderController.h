#pragma once

#include "rasterizer.h"
namespace sora {
	class RenderController {
	public:
		RenderController(uint32 width, uint32 height) :mViewportWidth(width), mViewportHeight(height), mRaster(width, height){
			mZBuffer.resize(width * height);
		}

		inline std::shared_ptr<Camera> GetCamera() { return mCamera; }

		inline void SetWriter(Rasterizer::FrameBufferWriter writer) { mWriter = writer; }
		inline void SetIlluminare(std::shared_ptr<Illuminare> light) { 
			mLight = light;
			vec3 position = vec3(mObjFrames[0]*vec4(0.0,0.0,0.0,1.0f));
			vec3 target = position + 5.0f*mLight->GetDirection();
			mat4 lightViewMatrix = glm::lookAt(target, position, vec3(0.0f, -1.0f, 0.0f));
			mLight->SetCamera(std::make_shared<Camera>(lightViewMatrix, ProjectionType::Orthogonal, 0, 10,mViewportHeight/mViewportWidth,1,9));
		}
		inline void SetCamera(std::shared_ptr<Camera> camera) { mCamera = camera; }

		inline void AddDrawCall(DrawCallData data, mat4 objFrame, std::shared_ptr<Texture> texture, bool useAmbient, bool castShadow, bool depthTest, bool depthWrite, float ambientRadiance = 0) {
			mDatas.push_back(data);
			mObjFrames.push_back(objFrame);
			mTextures.push_back(texture);
			mUseAmbients.push_back(useAmbient);
			mCastShadows.push_back(castShadow);
			mDepthTests.push_back(depthTest);
			mDepthWrites.push_back(depthWrite);
			mAmbientRadiances.push_back(ambientRadiance);
			// shadow map should be updated
			mInitialized = false;
		}

		inline void EnableVisualizeDepthBuffer(bool enable) { mVisualizeDepthBuffer = enable; }
		inline void EnableVisualizeShadowMap(bool enable) { mVisualizeShadowMap = enable; }
		void Render();

	private:
		std::vector<DrawCallData> mDatas;
		std::vector<mat4> mObjFrames;
		std::vector<std::shared_ptr<Texture>> mTextures;

		std::vector<bool> mUseAmbients;
		std::vector<bool> mCastShadows;
		std::vector<bool> mDepthTests;
		std::vector<bool> mDepthWrites;
		std::vector<float> mAmbientRadiances;

		std::shared_ptr<Illuminare> mLight;
		std::shared_ptr<Camera> mCamera;

		uint16 mViewportWidth{ 0 };
		uint16 mViewportHeight{ 0 };

		std::vector<float> mZBuffer;
		std::vector<float> mShadowMap;

		Rasterizer mRaster;
		Rasterizer::FrameBufferWriter mWriter;

		bool mVisualizeShadowMap = false;
		bool mVisualizeDepthBuffer = false;
		bool mInitialized = false;
	};
}