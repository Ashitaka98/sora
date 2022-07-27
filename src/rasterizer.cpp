#include"rasterizer.h"
#include"utils.h"
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
namespace sora {


	
	void Rasterizer::Rasterize() {

        //initialize window and camera parameters
        float aspect_ratio = mViewportHeight / mViewportWidth;
        const float fieldOfView = mCamera->GetFov();
        float near = 1;
        float far = 9;
        float shift_x = 0;
        float shift_y = 0;

        // perspective projection
        mat4 cameraFrameInv = mCamera->GetCameraFrameInv();
        mat4 perspectiveMatrix = MatrixPerspectiveProjection(fieldOfView, aspect_ratio, vec2(shift_x, shift_y), near, far);
        mat4 viewportMatrix = MatrixViewportTransform(mViewportWidth, mViewportHeight);

        uint32 vertexNum = vbSize / mLayout.GetStride();
        std::vector<vec4> clippingBuffer;
        std::vector<vec4> viewportBuffer;
        clippingBuffer.resize(vertexNum);
        viewportBuffer.resize(vertexNum);
        for (uint32 i=0; i < vertexNum; i++) {
            vec4 objectCoord = mLayout.GetPosition(mVertexBuffer, i);
            vec4 worldCoord = mObjectCoordFrame * objectCoord;
            vec4 cameraCoord = cameraFrameInv * worldCoord;
            vec4 clippingCoord = perspectiveMatrix * cameraCoord;
            vec4 ndcCoord = clippingCoord / clippingCoord[3];
            vec4 viewportCoord = viewportMatrix * ndcCoord;
            viewportBuffer[i] = viewportCoord;
            clippingBuffer[i] = clippingCoord;
        }

        uint32* ib = reinterpret_cast<uint32*>(mIndexBuffer);
        for (uint32 i=0; i < primitiveNum; i++) {
            uint32 A = ib[3*i];
            uint32 B = ib[3*i + 1];
            uint32 C = ib[3*i + 2];
            // a bounding box for a triangle projected to display window
            int boundary_x_min = MIN(MIN(viewportBuffer[A].x, viewportBuffer[B].x), viewportBuffer[C].x);
            int boundary_x_max = MAX(MAX(viewportBuffer[A].x, viewportBuffer[B].x), viewportBuffer[C].x);
            int boundary_y_min = MIN(MIN(viewportBuffer[A].y, viewportBuffer[B].y), viewportBuffer[C].y);
            int boundary_y_max = MAX(MAX(viewportBuffer[A].y, viewportBuffer[B].y), viewportBuffer[C].y);

            // test pixels in bounding box
            for (int i = boundary_y_min; i <= boundary_y_max; i++) {
                for (int j = boundary_x_min; j <= boundary_x_max; j++) {
                    vec3 barycentric = BarycentricCoordinate(vec2(viewportBuffer[A]), vec2(viewportBuffer[B]), vec2(viewportBuffer[C]), vec2(j, i));
                    // shade pixels inside triangles
                    if (barycentric.x >= 0 && barycentric.x <= 1 && barycentric.y >= 0 && barycentric.y <= 1 && barycentric.z >= 0 && barycentric.z <= 1) {
                        float w_n_inverse_a = 1 / clippingBuffer[A].w;
                        float w_n_inverse_b = 1 / clippingBuffer[B].w;
                        float w_n_inverse_c = 1 / clippingBuffer[C].w;
                        float w_n_inverse_interpolated = barycentric.x * w_n_inverse_a + barycentric.y * w_n_inverse_b + barycentric.z * w_n_inverse_c;
                        
                        float z_interpolated = (barycentric.x * w_n_inverse_a * viewportBuffer[A].z + barycentric.y* w_n_inverse_b * viewportBuffer[B].z + barycentric.z* w_n_inverse_c * viewportBuffer[C].z)/w_n_inverse_interpolated;

                        if (!mDepthTest|| z_interpolated < mZBuffer[i*mViewportWidth + j]) {

                            // transform illuminant from world coordinate frame to triangle's object coordinate frame for shading
                            vec3  direction = - mat3(mObjectFrameInv) * mLight->GetDirection();
                            
                            
                            // update z-buffer
                            if(mDepthWrite)
                                mZBuffer[i*mViewportWidth + j] = z_interpolated;

                            // interpolate to get pixel color, will be replaced by texture sampling
                            // vec3 color_interpolated = barycentric.x * obj_cube[k].color_a + barycentric.y * obj_cube[k].color_b + barycentric.z * obj_cube[k].color_c;;

                            // texture sampling, with perspective amendent interpolation
                            vec2 tex_coord_interpolated = (barycentric.x * w_n_inverse_a * mLayout.GetTexCoor(mVertexBuffer,A) + barycentric.y * w_n_inverse_b * mLayout.GetTexCoor(mVertexBuffer,B) + barycentric.z * w_n_inverse_c * mLayout.GetTexCoor(mVertexBuffer,C)) / w_n_inverse_interpolated;
                            
                            ubvec3 color = mTexture->Sample(tex_coord_interpolated);

                            // interpolate to get pixel normal vector
                            vec3 normal_interpolated = (barycentric.x *w_n_inverse_a* mLayout.GetNormal(mVertexBuffer,A) + barycentric.y * w_n_inverse_b * mLayout.GetNormal(mVertexBuffer,B) + barycentric.z* w_n_inverse_c * mLayout.GetNormal(mVertexBuffer,C))/w_n_inverse_interpolated;
                            normal_interpolated = glm::normalize(normal_interpolated);  // normalize the vector interpolated

                            float illuminant = mAmbientRadiance + MAX(glm::dot(direction, normal_interpolated), 0) * mLight->GetIntensity();
                            
                            mWriter(mViewportHeight - i, j, ubvec3(illuminant*vec3(color)));
                        }
                    }
                }
            }
        }

        
	}
}