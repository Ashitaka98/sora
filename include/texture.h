#pragma once
#include <iostream>

#include"defines.h"
#define MIN(x,y) (x<y?x:y)
namespace sora {
	//RGBAu8 Texture
	class Texture {
	public:
		Texture(std::string path);
		~Texture();
		inline ubvec3 Sample(uint16_t u, uint16_t v) {
			u = MIN(mWidth - 1, u);
			v = MIN(mHeight - 1, v);
			uint8_t r = mData[mChanns * mWidth * v + mChanns * u];
			uint8_t g = mData[mChanns * mWidth * v + mChanns * u + 1];
			uint8_t b = mData[mChanns * mWidth * v + mChanns * u + 2];
			return ubvec3{ r,g,b };
		}
		inline ubvec3 Sample(float u, float v) {
			uint16_t x = static_cast<uint16_t>(u * mWidth);
			uint16_t y = static_cast<uint16_t>(v * mHeight);
			return Sample(x, y);
		}
		inline ubvec3 Sample(vec2 uv) {
			uint16_t x = static_cast<uint16_t>(uv.x * mWidth);
			uint16_t y = static_cast<uint16_t>(uv.y * mHeight);
			return Sample(x, y);
		}
	private:
		uint8_t* mData{ nullptr };
		int mWidth{ 0 }, mHeight{ 0 }, mChanns{ 0 };
		std::string mPath{};
	};
}