#include"rasterizer.h"
#include"utilities.h"
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
namespace sora {
	Rasterizer::Rasterizer( const shared_ptr<vector<Vertex>>& pVertice,
                            const shared_ptr<vector<Triangle>>& pTris, 
                            const mat4& cameraCoordinateFrame, 
                            const mat4& objectCoordinateFrame, 
                            const uint16 width, 
                            const uint16 height,
                            callback writeColorBufferCallback)
		:_pVertice(pVertice),
        _pTris(pTris),
        _cameraCoordinateFrame(cameraCoordinateFrame),
        _objectCoordinateFrame(objectCoordinateFrame),
        _width(width),
        _height(height),
        _writeColorBuffer(writeColorBufferCallback)
        
	{
		_cameraFrameInv = inverse(cameraCoordinateFrame);
		_objectFrameInv = inverse(objectCoordinateFrame);
		_radianceAmbient = 0.5;                     
		_radianceDirectional = 0.5;                 
		_directionDirectional = normalize(vec4(1, 1, 1, 0));
		_zBuffer = unique_ptr<float[]>(new float[static_cast<uint32>(width) * height]);
	}

    void Rasterizer::setCameraFrame(const mat4& cameraCoordinateFrame) {
        _cameraCoordinateFrame = cameraCoordinateFrame;
        _cameraFrameInv = inverse(cameraCoordinateFrame);
    }

   

	
	void Rasterizer::rasterize() {

        //initialize window and camera parameters
        float aspect_ratio = _height / _width;
        const float fieldOfView = radians(90.f);
        float near = 1;
        float far = 9;
        float shift_x = 0;
        float shift_y = 0;

        //clear z-buffer
        for (int i=0;i<_width*_height; i++)
            _zBuffer.get()[i] = 1;

        // perspective projection
        mat4 perspectiveMatrix = matrixPerspectiveProjection(fieldOfView, aspect_ratio, vec2(shift_x, shift_y), near, far);
        mat4 viewportMatrix = matrixViewportTransform(_width, _height);
        for (auto it = _pVertice->begin(); it != _pVertice->end(); it++) {
            vec4 worldCoordinate = _objectCoordinateFrame * it->_coordinate;
            vec4 cameraCoordinate = _cameraFrameInv * worldCoordinate;
            it->_clippingCoordinate = perspectiveMatrix * cameraCoordinate;
            vec4 ndcCoordinate = it->_clippingCoordinate / it->_clippingCoordinate[3];
            it->_viewportCoordinate = viewportMatrix * ndcCoordinate;
        }

        for (auto it = _pTris->begin(); it != _pTris->end(); it++) {
            const Vertex& a = (*_pVertice)[it->_A];
            const Vertex& b = (*_pVertice)[it->_B];
            const Vertex& c = (*_pVertice)[it->_C];
            // a bounding box for a triangle projected to display window
            int boundary_x_min = MIN(MIN(a._viewportCoordinate.x, b._viewportCoordinate.x), c._viewportCoordinate.x);
            int boundary_x_max = MAX(MAX(a._viewportCoordinate.x, b._viewportCoordinate.x), c._viewportCoordinate.x);
            int boundary_y_min = MIN(MIN(a._viewportCoordinate.y, b._viewportCoordinate.y), c._viewportCoordinate.y);
            int boundary_y_max = MAX(MAX(a._viewportCoordinate.y, b._viewportCoordinate.y), c._viewportCoordinate.y);

            // test pixels in bounding box
            for (int i = boundary_y_min; i <= boundary_y_max; i++) {
                for (int j = boundary_x_min; j <= boundary_x_max; j++) {
                    vec3 barycentric = barycentric_coordinate(a._viewportCoordinate, b._viewportCoordinate, c._viewportCoordinate, vec2(j, i));
                    // shade pixels inside triangles
                    if (barycentric.x >= 0 && barycentric.x <= 1 && barycentric.y >= 0 && barycentric.y <= 1 && barycentric.z >= 0 && barycentric.z <= 1) {
                        float z_interpolated = barycentric.x * a._viewportCoordinate.z + barycentric.y * b._viewportCoordinate.z + barycentric.z * c._viewportCoordinate.z;

                        if (z_interpolated < _zBuffer[i*_width + j]) {

                            // transform illuminant from world coordinate frame to triangle's object coordinate frame for shading
                            vec3  direction = - mat3(_objectFrameInv) * _directionDirectional;

                            // update z-buffer
                            _zBuffer[i*_width + j] = z_interpolated;

                            // interpolate to get pixel color, will be replaced by texture sampling
                            // vec3 color_interpolated = barycentric.x * obj_cube[k].color_a + barycentric.y * obj_cube[k].color_b + barycentric.z * obj_cube[k].color_c;;

                            // texture sampling, with perspective amendent interpolation
                            float w_n_inverse_a = 1 / a._clippingCoordinate.w;
                            float w_n_inverse_b = 1 / b._clippingCoordinate.w;
                            float w_n_inverse_c = 1 / c._clippingCoordinate.w;
                            float w_n_inverse_interpolated = barycentric.x * w_n_inverse_a + barycentric.y * w_n_inverse_b + barycentric.z * w_n_inverse_c;
                            vec2 v_mul_w_n_inv_interpolated = barycentric.x * w_n_inverse_a * a._textureCoordinate + barycentric.y * w_n_inverse_b * b._textureCoordinate + barycentric.z * w_n_inverse_c * c._textureCoordinate;
                            vec2 tex_coord_interpolated = v_mul_w_n_inv_interpolated / w_n_inverse_interpolated;

                            tex_coord_interpolated.x = (int)tex_coord_interpolated.x;
                            tex_coord_interpolated.y = (int)tex_coord_interpolated.y;

                            // interpolate to get pixel normal vector
                            vec3 normal_interpolated = barycentric.x * a._normal + barycentric.y * b._normal + barycentric.z * c._normal;
                            normal_interpolated = normalize(normal_interpolated);  // normalize the vector interpolated

                            float illuminant = _radianceAmbient + MAX(dot(direction, normal_interpolated), 0) * _radianceDirectional;
                            //// shade the pixel
                            //vec3 color_shaded = (_radianceAmbient + MAX(dot(direction, normal_interpolated), 0) * _radianceDirectional) * vec3(color_fetched[0], color_fetched[1], color_fetched[2]);

                            //// write to frame buffer
                            //framebuffer_cv_mat.at<cv::Vec3b>(height - i, j) = cv::Vec3b(color_shaded.x, color_shaded.y, color_shaded.z);

                            _writeColorBuffer(_height - i, j, tex_coord_interpolated.y, tex_coord_interpolated.x, illuminant);
                        }
                    }
                }
            }
        }

        
	}
}