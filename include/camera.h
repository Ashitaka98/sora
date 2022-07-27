#pragma once
#include"defines.h"
namespace sora {
	class Camera {
	public:
		Camera() {}
		Camera(const mat4 &cameraFrame, const float fovAngle) :mCameraCoordFrame(cameraFrame),mFov(glm::radians(fovAngle)) {
			mCameraFrameInv = glm::inverse(mCameraCoordFrame);
		}

		inline float GetFov() {
			return mFov;
		}

		inline mat4 GetCameraFrame() { return mCameraCoordFrame; }

		inline mat4 GetCameraFrameInv() { return mCameraFrameInv; }

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
		float mFov{ 90.0f };
	};
}