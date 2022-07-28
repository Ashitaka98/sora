#include "renderController.h"
namespace sora {
	void RenderController::Render() {
		assert(mWriter);
		// calc shadow map once for one scene
		if (!mVisualizeDepthBuffer&&!mInitialized) {
			mShadowMap.resize(mViewportHeight * mViewportWidth);
			for (int i = 0; i < mViewportHeight * mViewportHeight; i++)
				mShadowMap[i] = 1.0f;
			bool needShadowMap = false;
			for (auto castShadow : mCastShadows)
				needShadowMap = needShadowMap || castShadow;
			if (needShadowMap) {
				mRaster.SetCamera(mLight->GetCamera());
				for (int i = 0; i < mDatas.size(); i++) {
					mRaster.mShading = false;
					mRaster.mDepthTest = true;
					mRaster.mDepthWrite = true;
					mRaster.SetData(mDatas[i]);
					mRaster.SetObjectCoordFrame(mObjFrames[i]);
					// write depth to shadow map 
					mRaster.Rasterize(mWriter, mShadowMap, mShadowMap);
				}
			}
			mInitialized = true;
		}
		// visualiza depth buffer if both flag enabled
		if (mVisualizeShadowMap&&!mVisualizeDepthBuffer) {
			for (int i = 0; i < mViewportHeight; i++) {
				for (int j = 0; j < mViewportWidth; j++) {
					mWriter(mViewportHeight - i, j, ubvec3(static_cast<uint8>(255 * mShadowMap[i * mViewportWidth + j])));
				}
			}
			return;
		}
		
		for (int i = 0; i < mViewportHeight * mViewportHeight; i++)
			mZBuffer[i] = 1.0f;

		mRaster.SetCamera(mCamera);
		for (int i = 0; i < mDatas.size(); i++) {
			mRaster.mDepthTest = mDepthTests[i];
			mRaster.mDepthWrite = mDepthWrites[i];
			mRaster.mAmbientRadiance = mAmbientRadiances[i];
			mRaster.mCastShadow = mCastShadows[i];
			mRaster.mUseAmbient = mUseAmbients[i];

			mRaster.SetData(mDatas[i]);
			mRaster.SetObjectCoordFrame(mObjFrames[i]);
			mRaster.SetTexture(mTextures[i]);

			mRaster.SetIlluminare(mLight);
			if (mVisualizeDepthBuffer)
				mRaster.mShading = false;
			else
				mRaster.mShading = true;

			mRaster.Rasterize(mWriter, mZBuffer, mShadowMap);
		}
		if (mVisualizeDepthBuffer) {
			for (int i = 0; i < mViewportHeight; i++) {
				for (int j = 0; j < mViewportWidth; j++) {
					mWriter(mViewportHeight - i, j, ubvec3(static_cast<uint8>(255 * mZBuffer[i * mViewportWidth + j])));
				}
			}
			return;
		}
	}
}