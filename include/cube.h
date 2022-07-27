#pragma once
#include <vector>
#include "defines.h"
namespace sora {
	// Cube is a demo geometry
	class Cube {
	private:
		Cube();
	public:
		static Cube* GetInstance() { return new Cube(); }
		uint8* GetVertexBuffer() { return mVertexBuffer.data(); }
		uint8* GetIndexBuffer() { return mIndexBuffer.data(); }
		uint32 GetVertexBufferSize() { return mVertexBuffer.size(); }
		uint32 GetIndexBufferSize() { return mIndexBuffer.size(); }
		uint32 GetPrimitiveNum() { return mPrimitiveNum; }
		VertexStreamLayout GetVertexStreamLayout() { return mLayout; }
	public:
		std::vector<uint8> mVertexBuffer;
		std::vector<uint8> mIndexBuffer;
		uint32 mPrimitiveNum;
		VertexStreamLayout mLayout;
	};
}