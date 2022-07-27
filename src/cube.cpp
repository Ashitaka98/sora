#include"cube.h"
namespace sora {
    Cube::Cube() {
        mLayout.AddVertexChannelLayout(VertexChannel::Position, VertexFormat::Float4);
        mLayout.AddVertexChannelLayout(VertexChannel::Normal, VertexFormat::Float3);
        mLayout.AddVertexChannelLayout(VertexChannel::TexCoord, VertexFormat::Float2);
        int vtxCount = 36;
        int idxCount = 36;
        mVertexBuffer.resize(vtxCount * mLayout.GetStride());
        mIndexBuffer.resize(idxCount * sizeof(uint32));
        mPrimitiveNum = 12;
        uint8* vb = mVertexBuffer.data();
        uint8* ib = mIndexBuffer.data();
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

        for (uint32 i = 0; i < vtxCount; i++) {
            memcpy(vb + mLayout.GetOffsets(VertexChannel::Position), &positions[i], sizeof(vec4));
            memcpy(vb + mLayout.GetOffsets(VertexChannel::Normal), &normals[i], sizeof(vec3));
            memcpy(vb + mLayout.GetOffsets(VertexChannel::TexCoord), &uvs[i], sizeof(vec2));
            vb += mLayout.GetStride();
        }

        for (uint32 i = 0; i < idxCount; i++) {
            memcpy(ib, &i, sizeof(uint32));
            ib += sizeof(uint32);
        }
    }
}