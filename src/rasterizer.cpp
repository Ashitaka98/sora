#include"rasterizer.h"
#include"utils.h"
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
namespace sora {

	void Rasterizer::Rasterize(FrameBufferWriter writer, std::vector<float>& zBuffer, std::vector<float>& shadowMap) {

        // perspective projection or orthogonal projection
        mat4 cameraFrameInv = mCamera->GetCameraFrameInv();
        mat4 projectionMatrix = mCamera->GetProjectionMatrix();
        mat4 viewportMatrix = MatrixViewportTransform(mViewportWidth, mViewportHeight);

        uint32 vertexNum = mData.vbSize / mData.mLayout.GetStride();
        std::vector<vec4> clippingBuffer;
        std::vector<vec4> viewportBuffer;
        clippingBuffer.resize(vertexNum);
        viewportBuffer.resize(vertexNum);
        for (uint32 i=0; i < vertexNum; i++) {
            vec4 objectCoord = mData.GetPosition(i);
            vec4 worldCoord = mObjectCoordFrame * objectCoord;
            vec4 cameraCoord = cameraFrameInv * worldCoord;
            vec4 clippingCoord = projectionMatrix * cameraCoord;
            vec4 NDCCoord = clippingCoord / clippingCoord[3];
            vec4 viewportCoord = viewportMatrix * NDCCoord;
            viewportBuffer[i] = viewportCoord;
            clippingBuffer[i] = clippingCoord;
        }

        uint32* ib = reinterpret_cast<uint32*>(mData.ib);
        for (uint32 i=0; i < mData.primitiveNum; i++) {
            uint32 A = ib[3*i];
            uint32 B = ib[3*i + 1];
            uint32 C = ib[3*i + 2];

            // back face culling
            vec3 AB = vec3(vec2(viewportBuffer[B] - viewportBuffer[A]), 0);
            vec3 AC = vec3(vec2(viewportBuffer[C] - viewportBuffer[A]), 0);
            bool isBackFace = glm::cross(AB, AC).z < 0;
            if (isBackFace)
                continue;

            // a bounding box for a triangle projected to display window
            float boundary_x_min = MIN(MIN(viewportBuffer[A].x, viewportBuffer[B].x), viewportBuffer[C].x);
            float boundary_x_max = MAX(MAX(viewportBuffer[A].x, viewportBuffer[B].x), viewportBuffer[C].x);
            float boundary_y_min = MIN(MIN(viewportBuffer[A].y, viewportBuffer[B].y), viewportBuffer[C].y);
            float boundary_y_max = MAX(MAX(viewportBuffer[A].y, viewportBuffer[B].y), viewportBuffer[C].y);

            // test pixels in bounding box
            for (int i = MAX(floor(boundary_y_min),0); i <= MIN(ceil(boundary_y_max),mViewportHeight-1); i++) {
                for (int j = MAX(floor(boundary_x_min),0); j <= MIN(ceil(boundary_x_max),mViewportWidth-1); j++) {
                    vec3 barycentric = BarycentricCoordinate(vec2(viewportBuffer[A]), vec2(viewportBuffer[B]), vec2(viewportBuffer[C]), vec2(j, i));
                    // shade pixels inside triangles
                    if (barycentric.x >= 0 && barycentric.x <= 1 && barycentric.y >= 0 && barycentric.y <= 1 && barycentric.z >= 0 && barycentric.z <= 1) {
                        float w_n_inverse_a = 1 / clippingBuffer[A].w;
                        float w_n_inverse_b = 1 / clippingBuffer[B].w;
                        float w_n_inverse_c = 1 / clippingBuffer[C].w;
                        float w_n_inverse_interpolated = barycentric.x * w_n_inverse_a + barycentric.y * w_n_inverse_b + barycentric.z * w_n_inverse_c;
                        
                        float z_interpolated = (barycentric.x  * viewportBuffer[A].z + barycentric.y * viewportBuffer[B].z + barycentric.z * viewportBuffer[C].z);

                        if (!mDepthTest|| z_interpolated < zBuffer[i*mViewportWidth + j]) {

                            // update z-buffer
                            if(mDepthWrite)
                                zBuffer[i*mViewportWidth + j] = z_interpolated;

                            if (mShading) {
                                bool occluded = false;
                                if (mCastShadow) {
                                    vec4 objectCoord = (barycentric.x * w_n_inverse_a * mData.GetPosition(A) + barycentric.y * w_n_inverse_b * mData.GetPosition(B) + barycentric.z * w_n_inverse_c * mData.GetPosition(C)) / w_n_inverse_interpolated;

                                    vec4 worldCoord = mObjectCoordFrame * objectCoord;
                                    vec4 cameraCoord = mLight->GetCamera()->GetCameraFrameInv() * worldCoord;
                                    vec4 clippingCoord = mLight->GetCamera()->GetProjectionMatrix() * cameraCoord;
                                    vec4 NDCCoord = clippingCoord / clippingCoord[3];
                                    vec4 viewportCoord = viewportMatrix * NDCCoord;
                                    float depth = viewportCoord.z;
                                    uint16 x = static_cast<uint16>(viewportCoord.x);
                                    uint16 y = static_cast<uint16>(viewportCoord.y);
                                    float depthSampled = shadowMap[y * mViewportWidth + x];
                                    // avoid z fighting
                                    if(depth>depthSampled+0.01f)
                                        occluded = true;
                                }
                                // transform illuminant from world coordinate frame to triangle's object coordinate frame for shading
                                vec3  direction = mat3(mObjectFrameInv) * mLight->GetDirection();

                                // texture sampling, with perspective amendent interpolation
                                vec2 tex_coord_interpolated = (barycentric.x * w_n_inverse_a * mData.GetTexCoor(A) + barycentric.y * w_n_inverse_b * mData.GetTexCoor(B) + barycentric.z * w_n_inverse_c * mData.GetTexCoor(C)) / w_n_inverse_interpolated;

                                ubvec3 color = mTexture->Sample(tex_coord_interpolated);

                                // interpolate to get pixel normal vector
                                vec3 normal_interpolated = (barycentric.x * w_n_inverse_a * mData.GetNormal(A) + barycentric.y * w_n_inverse_b * mData.GetNormal(B) + barycentric.z * w_n_inverse_c * mData.GetNormal(C)) / w_n_inverse_interpolated;
                                normal_interpolated = glm::normalize(normal_interpolated);  // normalize the vector interpolated

                                float illuminant = mAmbientRadiance + MAX(glm::dot(direction, normal_interpolated), 0) * (occluded?0.0f:mLight->GetIntensity());

                                writer(mViewportHeight - i, j, ubvec3(illuminant * vec3(color)));
                            }
                        }
                    }
                }
            }
        }

        
	}
}