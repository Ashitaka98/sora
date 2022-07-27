#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

#include "texture.h"

namespace sora {
	Texture::Texture(std::string path) {
		mPath = path;
		mData = stbi_load(mPath.c_str(), &mWidth, &mHeight, &mChanns, 0);
	}
	Texture::~Texture() {
		if (mData)
			stbi_image_free(mData);
	}
}