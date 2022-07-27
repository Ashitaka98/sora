#pragma once
#include<glm/glm.hpp>
#include<texture.h>
namespace sora {
	enum class IlluminareType
	{
		Directional=1,
		Point=2
	};
	class Illuminare {
	public:
		Illuminare(IlluminareType type, float intensity, glm::vec3 directionPosition):mType(type),mIntensity(intensity),mDirectionPosition(directionPosition) {

		}
		~Illuminare() {

		}
		inline float GetIntensity() { return mIntensity; }
		inline vec3 GetDirection() { return mDirectionPosition; }
	private:
		IlluminareType mType{};
		float mIntensity{ 0 };
		glm::vec3 mDirectionPosition{};		// Pointlight Position or Direional light direction

		mat4 mViewMatrix{};					// use for shadow map
		mat4 mViewMatrixInv{};
		std::shared_ptr<Texture> mShadowMap{};
	};
}