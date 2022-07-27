#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
namespace sora {

	using uint8 = glm::uint8_t;
	using uint16 = glm::uint16_t;
	using uint32 = glm::uint32_t;
	using vec2 = glm::vec2;
	using vec3 = glm::vec3;
	using vec4 = glm::vec4;
	using ubvec2 = glm::u8vec2;
	using ubvec3 = glm::u8vec3;
	using ubvec4 = glm::u8vec4;
	using mat3 = glm::mat3;
	using mat4 = glm::mat4;

	enum class ProjectionType {
		Perspective,
		Orthogonal
	};

	enum class VertexChannel {
		Position = 0,
		Color = 1,
		Normal = 2,
		TexCoord = 3,
		Max = 4
	};
	enum class VertexFormat {
		Float=sizeof(float),
		Float2=2*sizeof(float),
		Float3=3*sizeof(float),
		Float4=4*sizeof(float),
	};
	class VertexStreamLayout {
	public:
		VertexStreamLayout() {
			for (uint8 i = 0; i < static_cast<int>(VertexChannel::Max); i++) {
				mOffsets[i] = 0;
				mSize[i] = -1;
			}
		}
		inline bool HasChannel(VertexChannel channel) {
			return mSize[static_cast<int>(channel)] != -1;
		}
		inline uint16 GetStride() { return mStride; }
		inline vec4 GetPosition(uint8* vb, uint32 i) {
			vec4 ret;
			memcpy(&ret,
					vb + i * mStride + mOffsets[static_cast<int>(VertexChannel::Position)],
					mSize[static_cast<int>(VertexChannel::Position)]);
			return ret;
		}
		inline vec3 GetColor(uint8* vb, uint32 i) {
			vec3 ret;
			memcpy(&ret, vb + i * mStride + mOffsets[static_cast<int>(VertexChannel::Color)], mSize[static_cast<int>(VertexChannel::Color)]);
			return ret;
		}
		inline vec3 GetNormal(uint8* vb, uint32 i) {
			vec3 ret;
			memcpy(&ret, vb + i * mStride + mOffsets[static_cast<int>(VertexChannel::Normal)], mSize[static_cast<int>(VertexChannel::Normal)]);
			return ret;
		}
		inline vec2 GetTexCoor(uint8* vb, uint32 i) {
			vec2 ret;
			memcpy(&ret, vb + i * mStride + mOffsets[static_cast<int>(VertexChannel::TexCoord)], mSize[static_cast<int>(VertexChannel::TexCoord)]);
			return ret;
		}
		void AddVertexChannelLayout(VertexChannel channel, VertexFormat format) {
			mOffsets[static_cast<int>(channel)] = mStride;
			mStride += static_cast<int>(format);
			mSize[static_cast<int>(channel)] = static_cast<int>(format);
		}
		uint16 GetOffsets(VertexChannel channel) {
			return mOffsets[static_cast<int>(channel)];
		}
	private:
		uint16 mStride=0;
		uint16 mOffsets[static_cast<int>(VertexChannel::Max)];
		uint16 mSize[static_cast<int>(VertexChannel::Max)];
	};
}