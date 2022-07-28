#pragma once
#include<glm/glm.hpp>
#include<texture.h>
#include<camera.h>
namespace sora {
	class Illuminare {
	public:
		Illuminare(IlluminareType type, float intensity, glm::vec3 direction):mType(type),mIntensity(intensity),mDirection(direction) {
		}
		~Illuminare() {

		}
		inline void SetCamera(std::shared_ptr<Camera> camera) { mCamera = camera; }
		inline float GetIntensity() { return mIntensity; }
		inline vec3 GetDirection() { return mDirection; }
		inline std::shared_ptr<Camera> GetCamera() { return mCamera; }
	private:
		IlluminareType mType{};
		float mIntensity{ 0 };
		glm::vec3 mDirection{};		// Pointlight Position or Direional light direction

		std::shared_ptr<Camera> mCamera;
	};
}