#pragma once
#include <vector>
#include "defines.h"
namespace sora {
	// Cube is a demo geometry
	class Cube {
	public:
		static void CreateInstance(std::vector<uint8>& vb, std::vector<uint8>& ib, VertexStreamLayout& layout, uint32 &primitiveNum) {
            assert(layout.HasChannel(VertexChannel::Position) && layout.HasChannel(VertexChannel::Normal) && layout.HasChannel(VertexChannel::TexCoord));
            uint32 vbSize = vb.size();
            uint32 ibSize = ib.size();
            int vtxCount = vbSize/layout.GetStride();
            vb.resize(vbSize + 24 * layout.GetStride());
            ib.resize(ibSize + 36 * sizeof(uint32));
            primitiveNum += 12;
            std::vector<vec4> positions;
            std::vector<vec3> normals;
            std::vector<vec2> uvs;
            std::vector<uint32> index;

            positions.emplace_back(-1, 1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(0, 0);
            positions.emplace_back(1, 1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(1, 0);
            positions.emplace_back(1, -1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(1, 1);
            positions.emplace_back(-1, -1, 1, 1);
            normals.emplace_back(0, 0, 1);
            uvs.emplace_back(0, 1);
            index.push_back(vtxCount + 0);
            index.push_back(vtxCount + 3);
            index.push_back(vtxCount + 1);
            index.push_back(vtxCount + 3);
            index.push_back(vtxCount + 2);
            index.push_back(vtxCount + 1);

            positions.emplace_back(1, 1, 1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(1, 0);
            positions.emplace_back(1, 1, -1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(0, 0);
            positions.emplace_back(1, -1, -1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(1, -1, 1, 1);
            normals.emplace_back(1, 0, 0);
            uvs.emplace_back(1, 1);
            index.push_back(vtxCount + 4);
            index.push_back(vtxCount + 7);
            index.push_back(vtxCount + 5);
            index.push_back(vtxCount + 7);
            index.push_back(vtxCount + 6);
            index.push_back(vtxCount + 5);

            positions.emplace_back(1, 1, -1, 1);
            uvs.emplace_back(0, 0);
            normals.emplace_back(0, 0, -1);
            positions.emplace_back(-1, 1, -1, 1);
            normals.emplace_back(0, 0, -1);
            uvs.emplace_back(1, 0);
            positions.emplace_back(-1, -1, -1, 1);
            normals.emplace_back(0, 0, -1);
            uvs.emplace_back(1, 1);
            positions.emplace_back(1, -1, -1, 1);
            normals.emplace_back(0, 0, -1);
            uvs.emplace_back(0, 1);
            index.push_back(vtxCount + 8);
            index.push_back(vtxCount + 11);
            index.push_back(vtxCount + 9);
            index.push_back(vtxCount + 11);
            index.push_back(vtxCount + 10);
            index.push_back(vtxCount + 9);

            positions.emplace_back(-1, 1, -1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(1, 0);
            positions.emplace_back(-1, 1, 1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(0, 0);
            positions.emplace_back(-1, -1, 1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(-1, -1, -1, 1);
            normals.emplace_back(-1, 0, 0);
            uvs.emplace_back(1, 1);
            index.push_back(vtxCount + 12);
            index.push_back(vtxCount + 15);
            index.push_back(vtxCount + 13);
            index.push_back(vtxCount + 15);
            index.push_back(vtxCount + 14);
            index.push_back(vtxCount + 13);

            positions.emplace_back(-1, 1, -1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(1, 1, -1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(1, 1);
            positions.emplace_back(1, 1, 1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(1, 0);
            positions.emplace_back(-1, 1, 1, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(0, 0);
            index.push_back(vtxCount + 16);
            index.push_back(vtxCount + 19);
            index.push_back(vtxCount + 17);
            index.push_back(vtxCount + 19);
            index.push_back(vtxCount + 18);
            index.push_back(vtxCount + 17);

            positions.emplace_back(-1, -1, 1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(0, 1);
            positions.emplace_back(1, -1, 1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(1, 1);
            positions.emplace_back(1, -1, -1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(1, 0);
            positions.emplace_back(-1, -1, -1, 1);
            normals.emplace_back(0, -1, 0);
            uvs.emplace_back(0, 0);
            index.push_back(vtxCount + 20);
            index.push_back(vtxCount + 23);
            index.push_back(vtxCount + 21);
            index.push_back(vtxCount + 23);
            index.push_back(vtxCount + 22);
            index.push_back(vtxCount + 21);

            uint8* dest = &vb[vbSize];
            for (uint32 i = 0; i < positions.size(); i++) {
                memcpy(dest + layout.GetOffsets(VertexChannel::Position), &positions[i], sizeof(vec4));
                memcpy(dest + layout.GetOffsets(VertexChannel::Normal), &normals[i], sizeof(vec3));
                memcpy(dest + layout.GetOffsets(VertexChannel::TexCoord), &uvs[i], sizeof(vec2));
                dest += layout.GetStride();
            }
            memcpy(&ib[ibSize], index.data(), index.size() * sizeof(uint32));
		}
	};

    class Plane {
    public:
        static void CreateInstance(std::vector<uint8>& vb, std::vector<uint8>& ib, VertexStreamLayout& layout, uint32& primitiveNum) {
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
            positions.emplace_back(2, -1.1, -2, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(1, 0);
            positions.emplace_back(2, -1.1, 2, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(1, 1);
            positions.emplace_back(-2, -1.1, 2, 1);
            normals.emplace_back(0, 1, 0);
            uvs.emplace_back(0, 1);

            idx.push_back(vtxCount);
            idx.push_back(vtxCount+3);
            idx.push_back(vtxCount+1);
            idx.push_back(vtxCount+3);
            idx.push_back(vtxCount+2);
            idx.push_back(vtxCount+1);

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