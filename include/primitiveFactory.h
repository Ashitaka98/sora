#pragma once
#include <vector>
#include "defines.h"
namespace sora {
	// Cube is a demo geometry
	class Cube {
	public:
		static void GetInstance(std::vector<uint8>& vb, std::vector<uint8>& ib, VertexStreamLayout& layout, uint32 &primitiveNum) {
            assert(layout.HasChannel(VertexChannel::Position) && layout.HasChannel(VertexChannel::Normal) && layout.HasChannel(VertexChannel::TexCoord));
            uint32 vbSize = vb.size();
            uint32 ibSize = ib.size();
            int vtxCount = vbSize/layout.GetStride();
            vb.resize(vbSize + 36 * layout.GetStride());
            ib.resize(ibSize + 36 * sizeof(uint32));
            primitiveNum += 12;
            std::vector<vec4> positions;
            std::vector<vec3> normals;
            std::vector<vec2> uvs;

            positions.emplace_back(-1, 1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(0, 0);
            positions.emplace_back(1, 1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(1, 0);
            positions.emplace_back(-1, -1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(0, 1);
            positions.emplace_back(1, -1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(1, 1);
            positions.emplace_back(-1, -1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(0, 1);
            positions.emplace_back(1, 1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(1, 0);

            positions.emplace_back(1, -1, 1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(1, 1);
            positions.emplace_back(1, 1, 1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(1, 0);
            positions.emplace_back(1, -1, -1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(1, 1, -1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(0, 0);
            positions.emplace_back(1, -1, -1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(1, 1, 1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(1, 0);

            positions.emplace_back(1, 1, -1, 1);
            uvs.emplace_back(0, 0);
            normals.emplace_back(0, 0, -1);
            positions.emplace_back(-1, 1, -1, 1);
            normals.emplace_back(0, 0, -1);
            uvs.emplace_back(1, 0);
            positions.emplace_back(1, -1, -1, 1);
            normals.emplace_back(0, 0, -1);
            uvs.emplace_back(0, 1);
            positions.emplace_back(-1, -1, -1, 1);
            normals.emplace_back(0, 0, -1);
            uvs.emplace_back(1, 1);
            positions.emplace_back(1, -1, -1, 1);
            normals.emplace_back(0, 0, -1);
            uvs.emplace_back(0, 1);
            positions.emplace_back(-1, 1, -1, 1);
            normals.emplace_back(0, 0, -1);
            uvs.emplace_back(1, 0);

            positions.emplace_back(-1, -1, -1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(1, 1);
            positions.emplace_back(-1, 1, -1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(1, 0);
            positions.emplace_back(-1, -1, 1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(-1, 1, 1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(0, 0);
            positions.emplace_back(-1, -1, 1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(-1, 1, -1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(1, 0);

            positions.emplace_back(1, 1, -1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(1, 1);
            positions.emplace_back(1, 1, 1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(1, 0);
            positions.emplace_back(-1, 1, -1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(-1, 1, 1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(0, 0);
            positions.emplace_back(-1, 1, -1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(1, 1, 1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(1, 0);

            positions.emplace_back(1, -1, 1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(1, 1);
            positions.emplace_back(1, -1, -1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(1, 0);
            positions.emplace_back(-1, -1, 1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(-1, -1, -1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(0, 0);
            positions.emplace_back(-1, -1, 1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(1, -1, -1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(1, 0);

            uint8* dest = &vb[vbSize];
            for (uint32 i = 0; i < 36; i++) {
                memcpy(dest + layout.GetOffsets(VertexChannel::Position), &positions[i], sizeof(vec4));
                memcpy(dest + layout.GetOffsets(VertexChannel::Normal), &normals[i], sizeof(vec3));
                memcpy(dest + layout.GetOffsets(VertexChannel::TexCoord), &uvs[i], sizeof(vec2));
                dest += layout.GetStride();
            }
            dest = &ib[ibSize];
            for (uint32 i = vtxCount; i < vtxCount+36; i++) {
                memcpy(dest, &i, sizeof(uint32));
                dest += sizeof(uint32);
            }
		}
	};

    class Plane {
    public:
        static void GetInstance(std::vector<uint8>& vb, std::vector<uint8>& ib, VertexStreamLayout& layout, uint32& primitiveNum) {
            assert(layout.HasChannel(VertexChannel::Position) && layout.HasChannel(VertexChannel::Normal) && layout.HasChannel(VertexChannel::TexCoord));
            uint32 vbSize = vb.size();
            uint32 ibSize = ib.size();
            int vtxCount = vbSize / layout.GetStride();
            vb.resize(vbSize + 4 * layout.GetStride());
            ib.resize(ibSize + 6 * sizeof(uint32));
            primitiveNum += 2;
            std::vector<vec4> positions;
            std::vector<vec3> normals;
            std::vector<vec2> uvs;
            std::vector<uint32> idx;

            positions.emplace_back(-2, -1.1, -2, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(0, 0);
            positions.emplace_back(-2, -1.1, 2, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(2, -1.1, 2, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(1, 1);
            positions.emplace_back(2, -1.1, -2, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(1, 0);

            idx.push_back(vtxCount);
            idx.push_back(vtxCount+1);
            idx.push_back(vtxCount+2);
            idx.push_back(vtxCount);
            idx.push_back(vtxCount+2);
            idx.push_back(vtxCount+3);

            uint8* dest = &vb[vbSize];
            for (uint32 i = 0; i < positions.size(); i++) {
                memcpy(dest + layout.GetOffsets(VertexChannel::Position), &positions[i], sizeof(vec4));
                memcpy(dest + layout.GetOffsets(VertexChannel::Normal), &normals[i], sizeof(vec3));
                memcpy(dest + layout.GetOffsets(VertexChannel::TexCoord), &uvs[i], sizeof(vec2));
                dest += layout.GetStride();
            }

            memcpy(&ib[ibSize], idx.data(), idx.size() * sizeof(uint32));
        }
    };
}