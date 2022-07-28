#pragma once
#include"defines.h"
#include"utils.h"
namespace sora {
	class Camera {
	public:
		Camera(const mat4 &cameraFrame, ProjectionType projType=ProjectionType::Perspective, const float fovAngle=90, const float width=5,const float aspectRatio=1,const float _zNear=1, const float _zFar=9) :
			mCameraCoordFrame(cameraFrame),mProjType(projType),mFov(glm::radians(fovAngle)),mWidth(width),mAspectRatio(aspectRatio), zNear(_zNear),zFar(_zFar) {
			mCameraFrameInv = glm::inverse(mCameraCoordFrame);
			if (mProjType == ProjectionType::Perspective)
				mProjectionMatrix = MatrixPerspectiveProjection(mFov, mAspectRatio, vec2(0, 0), zNear, zFar);
			else if (mProjType == ProjectionType::Orthogonal) {
				float left = -mWidth / 2;
				float right = mWidth / 2;
				float bottom = -mWidth * mAspectRatio / 2;
				float top = mWidth * mAspectRatio / 2;

				mProjectionMatrix = MatrixOrthogonalProjection(left, right, bottom, top, zNear, zFar);
			}
			else
				assert(false);
		}

		inline float GetFov() {
			return mFov;
		}

		inline mat4 GetCameraFrame() { return mCameraCoordFrame; }

		inline mat4 GetCameraFrameInv() { return mCameraFrameInv; }

		inline mat4 GetProjectionMatrix() { return mProjectionMatrix; }

		inline void SetCameraFrame(const mat4 &cameraFrame) {
			mCameraCoordFrame = cameraFrame;
			mCameraFrameInv = glm::inverse(mCameraCoordFrame);
		}
		inline void RotateAroundLookat(const mat4& rotateMatrix, const mat4& lookatFrame) {
			mCameraCoordFrame = lookatFrame * rotateMatrix * glm::inverse(lookatFrame) * mCameraCoordFrame;
			mCameraFrameInv = glm::inverse(mCameraCoordFrame);
		}
		static mat4 GetRotateMatrixX(const float rotAngle){
			float rotRadiance = glm::radians(rotAngle);
			return glm::rotate(mat4(1), rotRadiance, vec3(1, 0, 0));
		}
		static mat4 GetRotateMatrixY(const float rotAngle) {
			float rotRadiance = glm::radians(rotAngle);
			return glm::rotate(mat4(1), rotRadiance, vec3(0, 1, 0));
		}
	private:
		mat4 mCameraCoordFrame{};
		mat4 mCameraFrameInv{};
		mat4 mProjectionMatrix{};
		
		ProjectionType mProjType{ ProjectionType::Perspective };

		float mAspectRatio{ 1 };
		float zNear{ 1 }, zFar{ 9 };
		float mFov{ 90.0f };
		float mWidth{ 5 };
	};
}