#include <opencv2/opencv.hpp>
#include "transformations.h"
#include "triangle.h"
#include "utilities.h"
#define height  512
#define width  512


// camera coordinate frame transformation_matrix with respect to world coordinate
glm::mat4 camera_coordinate_frame;
glm::mat4 camera_frame_inv;

// z-buffer
float z_buffer[height][width];

// scene illuminant 
float radiance_ambient = 0.5;                     // ambient light
float radiance_directional = 0.5;                 // directional light
glm::vec4 direction_directional = glm::normalize(glm::vec4(1,1,1,0));            // direction of the directional light, which is a unit vector given in world coordinate frame 

// mouse event handler
//void onMouseEvent(int event, int x, int y, int flag, void* ustc);

int main(int argc, char const* argv[]) {
    
    //initialize window and camera parameters
    float aspect_ratio = height / width;
    const float field_of_view = glm::radians(90.f);
    float near = 1;
    float far = 9;
    float shift_x = 0;
    float shift_y = 0;

    // create framebuffer
    static const char kWindowName[] = "sora";
    cv::Mat framebuffer_cv_mat = cv::Mat::zeros(height, width, CV_8UC3);

    // load texture image
    cv::Mat texture_image = cv::imread("C:\\Work\\Projects\\sora\\x64\\Debug\\checkboard.png");
    if (texture_image.empty()) {
        std::cout << "texture image load failure\n";
        return 0;
    }
    int texture_width = texture_image.cols;
    int texture_height = texture_image.rows;

    // create window
    cv::namedWindow(kWindowName, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);
    cv::resizeWindow(kWindowName, cv::Size(width, height));
    cv::setWindowTitle(kWindowName, kWindowName);
    //cv::setMouseCallback(kWindowName, onMouseEvent,(void*)&camera_coordinate_frame);
    
    //initialize camera coordinate frame
    camera_coordinate_frame = glm::mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 1, 1
    );
    camera_frame_inv = glm::inverse(camera_coordinate_frame);

    //initialize object coordinate frame with respect to world coordinate frame
    glm::mat4 object_coordinate_frame(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, -3, 1
    );
    glm::mat4 object_frame_inv = glm::inverse(object_coordinate_frame);


    //-------------------------------- initialize a cube composed of 12 triangles ---------------------------------------------

    // set shared object coordinate frame for triangles
    Triangle obj_cube[12];    // default constructor
    for (int i = 0; i < 12; i++) {
        obj_cube[i].p_object_coordinate_frame = &object_coordinate_frame;
        obj_cube[i].p_object_frame_inv = &object_frame_inv;
    }

    // set vertex coordinate for each triangle
    obj_cube[0].a = glm::vec4(-1, 1, 1, 1);
    obj_cube[0].b = glm::vec4(1, 1, 1, 1);
    obj_cube[0].c = glm::vec4(-1, -1, 1, 1);
    obj_cube[1].a = glm::vec4(1, -1, 1, 1);
    obj_cube[1].b = glm::vec4(-1, -1, 1, 1);
    obj_cube[1].c = glm::vec4(1, 1, 1, 1);
    obj_cube[2].a = glm::vec4(1, -1, 1, 1);
    obj_cube[2].b = glm::vec4(1, 1, 1, 1);
    obj_cube[2].c = glm::vec4(1, -1, -1, 1);
    obj_cube[3].a = glm::vec4(1, 1, -1, 1);
    obj_cube[3].b = glm::vec4(1, -1, -1, 1);
    obj_cube[3].c = glm::vec4(1, 1, 1, 1);
    obj_cube[4].a = glm::vec4(1, 1, -1, 1);
    obj_cube[4].b = glm::vec4(-1, 1, -1, 1);
    obj_cube[4].c = glm::vec4(1, -1, -1, 1);
    obj_cube[5].a = glm::vec4(-1, -1, -1, 1);
    obj_cube[5].b = glm::vec4(1, -1, -1, 1);
    obj_cube[5].c = glm::vec4(-1, 1, -1, 1);
    obj_cube[6].a = glm::vec4(-1, -1, -1, 1);
    obj_cube[6].b = glm::vec4(-1, 1, -1, 1);
    obj_cube[6].c = glm::vec4(-1, -1, 1, 1);
    obj_cube[7].a = glm::vec4(-1, 1, 1, 1);
    obj_cube[7].b = glm::vec4(-1, -1, 1, 1);
    obj_cube[7].c = glm::vec4(-1, 1, -1, 1);
    obj_cube[8].a = glm::vec4(1, 1, -1, 1);
    obj_cube[8].b = glm::vec4(1, 1, 1, 1);
    obj_cube[8].c = glm::vec4(-1, 1, -1, 1);
    obj_cube[9].a = glm::vec4(-1, 1, 1, 1);
    obj_cube[9].b = glm::vec4(-1, 1, -1, 1);
    obj_cube[9].c = glm::vec4(1, 1, 1, 1);
    obj_cube[10].a = glm::vec4(1, -1, 1, 1);
    obj_cube[10].b = glm::vec4(1, -1, -1, 1);
    obj_cube[10].c = glm::vec4(-1, -1, 1, 1);
    obj_cube[11].a = glm::vec4(-1, -1, -1, 1);
    obj_cube[11].b = glm::vec4(-1, -1, 1, 1);
    obj_cube[11].c = glm::vec4(1, -1, -1, 1);

    // set vertex normal for each triangle
    obj_cube[0].normal_a = glm::vec4(0, 0, 1,0);
    obj_cube[0].normal_b = glm::vec4(0, 0, 1,0);
    obj_cube[0].normal_c = glm::vec4(0, 0, 1,0);
    obj_cube[1].normal_a = glm::vec4(0, 0, 1, 0);
    obj_cube[1].normal_b = glm::vec4(0, 0, 1, 0);
    obj_cube[1].normal_c = glm::vec4(0, 0, 1, 0);
    obj_cube[2].normal_a = glm::vec4(1, 0, 0,0);
    obj_cube[2].normal_b = glm::vec4(1, 0, 0,0);
    obj_cube[2].normal_c = glm::vec4(1, 0, 0, 0);
    obj_cube[3].normal_a = glm::vec4(1, 0, 0, 0);
    obj_cube[3].normal_b = glm::vec4(1, 0, 0, 0);
    obj_cube[3].normal_c = glm::vec4(1, 0, 0, 0);
    obj_cube[4].normal_a = glm::vec4(0, 0, -1, 0);
    obj_cube[4].normal_b = glm::vec4(0, 0, -1, 0);
    obj_cube[4].normal_c = glm::vec4(0, 0, -1, 0);
    obj_cube[5].normal_a = glm::vec4(0, 0, -1, 0);
    obj_cube[5].normal_b = glm::vec4(0, 0, -1, 0);
    obj_cube[5].normal_c = glm::vec4(0, 0, -1, 0);
    obj_cube[6].normal_a = glm::vec4(-1, 0, 0, 0);
    obj_cube[6].normal_b = glm::vec4(-1, 0, 0, 0);
    obj_cube[6].normal_c = glm::vec4(-1, 0, 0, 0);
    obj_cube[7].normal_a = glm::vec4(-1, 0, 0, 0);
    obj_cube[7].normal_b = glm::vec4(-1, 0, 0, 0);
    obj_cube[7].normal_c = glm::vec4(-1, 0, 0, 0);
    obj_cube[8].normal_a = glm::vec4(0, 1, 0, 0);
    obj_cube[8].normal_b = glm::vec4(0, 1, 0, 0);
    obj_cube[8].normal_c = glm::vec4(0, 1, 0, 0);
    obj_cube[9].normal_a = glm::vec4(0, 1, 0, 0);
    obj_cube[9].normal_b = glm::vec4(0, 1, 0, 0);
    obj_cube[9].normal_c = glm::vec4(0, 1, 0, 0);
    obj_cube[10].normal_a = glm::vec4(0, -1, 0, 0);
    obj_cube[10].normal_b = glm::vec4(0, -1, 0, 0);
    obj_cube[10].normal_c = glm::vec4(0, -1, 0, 0);
    obj_cube[11].normal_a = glm::vec4(0, -1, 0, 0);
    obj_cube[11].normal_b = glm::vec4(0, -1, 0, 0);
    obj_cube[11].normal_c = glm::vec4(0, -1, 0, 0);

    // set vertex texture coordinate for each triangle
    obj_cube[0].tex_coord_a = glm::vec2(0, 0);
    obj_cube[0].tex_coord_b = glm::vec2(511, 0);
    obj_cube[0].tex_coord_c = glm::vec2(0, 511);
    obj_cube[1].tex_coord_a = glm::vec2(511, 511);
    obj_cube[1].tex_coord_b = glm::vec2(0, 511);
    obj_cube[1].tex_coord_c = glm::vec2(511, 0);
    obj_cube[2].tex_coord_a = glm::vec2(511, 511);
    obj_cube[2].tex_coord_b = glm::vec2(511, 0);
    obj_cube[2].tex_coord_c = glm::vec2(0, 511);
    obj_cube[3].tex_coord_a = glm::vec2(0, 0);
    obj_cube[3].tex_coord_b = glm::vec2(0, 511);
    obj_cube[3].tex_coord_c = glm::vec2(511, 0);
    obj_cube[4].tex_coord_a = glm::vec2(0, 0);
    obj_cube[4].tex_coord_b = glm::vec2(511, 0);
    obj_cube[4].tex_coord_c = glm::vec2(0, 511);
    obj_cube[5].tex_coord_a = glm::vec2(511, 511);
    obj_cube[5].tex_coord_b = glm::vec2(0, 511);
    obj_cube[5].tex_coord_c = glm::vec2(511, 0);
    obj_cube[6].tex_coord_a = glm::vec2(511, 511);
    obj_cube[6].tex_coord_b = glm::vec2(511, 0);
    obj_cube[6].tex_coord_c = glm::vec2(0, 511);
    obj_cube[7].tex_coord_a = glm::vec2(0, 0);
    obj_cube[7].tex_coord_b = glm::vec2(0, 511);
    obj_cube[7].tex_coord_c = glm::vec2(511, 0);
    obj_cube[8].tex_coord_a = glm::vec2(511, 511);
    obj_cube[8].tex_coord_b = glm::vec2(511, 0);
    obj_cube[8].tex_coord_c = glm::vec2(0, 511);
    obj_cube[9].tex_coord_a = glm::vec2(0, 0);
    obj_cube[9].tex_coord_b = glm::vec2(0, 511);
    obj_cube[9].tex_coord_c = glm::vec2(511, 0);
    obj_cube[10].tex_coord_a = glm::vec2(511, 511);
    obj_cube[10].tex_coord_b = glm::vec2(511, 0);
    obj_cube[10].tex_coord_c = glm::vec2(0, 511);
    obj_cube[11].tex_coord_a = glm::vec2(0, 0);
    obj_cube[11].tex_coord_b = glm::vec2(0, 511);
    obj_cube[11].tex_coord_c = glm::vec2(511, 0);
    //----------------------------------------------------------------------------------------------------------------------------


    //--------------------------------- matrix for view rotation in object coordinate frame ---------------------------------

    // rotation matrix provoked by key event
    const float rot_angle = glm::radians(15.f);
    glm::mat4 mat_rot_y = glm::rotate(glm::mat4(1), rot_angle, glm::vec3(0, 1, 0));
    glm::mat4 mat_rot_y_inv = glm::inverse(mat_rot_y);
    glm::mat4 mat_rot_x = glm::rotate(glm::mat4(1), rot_angle, glm::vec3(1, 0, 0));
    glm::mat4 mat_rot_x_inv = glm::inverse(mat_rot_x);

    //-----------------------------------------------------------------------------------------------------------------------


    //----------------------------------------- render loop ------------------------------------------------------------
    while (true) {

        // clear frame buffer
        framebuffer_cv_mat = cv::Mat::zeros(height, width, CV_8UC3);
        // reset z-buffer
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                z_buffer[i][j] = 1;

        // handle key events
        int key = cv::waitKey(100);
        if (key == 'q') {
            cv::destroyWindow(kWindowName);
            break;
        }
        switch (key) {
        case 'd':
            camera_coordinate_frame = object_coordinate_frame * mat_rot_y_inv * object_frame_inv * camera_coordinate_frame;
            camera_frame_inv = glm::inverse(camera_coordinate_frame);
            break;
        case 'a':
            camera_coordinate_frame = object_coordinate_frame * mat_rot_y * object_frame_inv * camera_coordinate_frame;
            camera_frame_inv = glm::inverse(camera_coordinate_frame);
            break;
        case 's':
            camera_coordinate_frame = object_coordinate_frame * mat_rot_x * object_frame_inv * camera_coordinate_frame;
            camera_frame_inv = glm::inverse(camera_coordinate_frame);
            break;
        case 'w':
            camera_coordinate_frame = object_coordinate_frame * mat_rot_x_inv * object_frame_inv * camera_coordinate_frame;
            camera_frame_inv = glm::inverse(camera_coordinate_frame);
            break;
        }

        // actual rendering should happen here!
        // TODO: render

        // convert object coordinate to camera coordinate
        Triangle camera_cube[12];
        for (int i = 0; i < 12; i++) {
            Triangle world_temp = obj_cube[i].obj2world();
            camera_cube[i] = world_temp.world2cam();
        }

        // perspective projection
        glm::mat4 perspective_matrix = matrix_PerspectiveProjection(field_of_view, aspect_ratio, glm::vec2(shift_x, shift_y), near, far);
        Triangle clipping_cube[12];
        for (int i = 0; i < 12; i++) {
            clipping_cube[i].a = perspective_matrix * camera_cube[i].a;
            clipping_cube[i].b = perspective_matrix * camera_cube[i].b;
            clipping_cube[i].c = perspective_matrix * camera_cube[i].c;
        }

        // clipping


        // perspective divide
        Triangle NDC_cube[12];
        for (int i = 0; i < 12; i++) {
            NDC_cube[i].a = clipping_cube[i].a / clipping_cube[i].a[3];
            NDC_cube[i].b = clipping_cube[i].b / clipping_cube[i].b[3];
            NDC_cube[i].c = clipping_cube[i].c / clipping_cube[i].c[3];
        }

        // backface culling


        // viewport transform
        glm::mat4 viewport_matrix = matrix_viewportTransform(width, height);
        Triangle window_cube[12];
        for (int i = 0; i < 12; i++) {
            window_cube[i].a = viewport_matrix * NDC_cube[i].a;
            window_cube[i].b = viewport_matrix * NDC_cube[i].b;
            window_cube[i].c = viewport_matrix * NDC_cube[i].c;
        }

        // rasterization
        for (int k = 0; k < 12; k++) {

            // a bounding box for triangle projected to display window
            int boundary_x_min = MIN(MIN(window_cube[k].a.x, window_cube[k].b.x), window_cube[k].c.x);
            int boundary_x_max = MAX(MAX(window_cube[k].a.x, window_cube[k].b.x), window_cube[k].c.x);
            int boundary_y_min = MIN(MIN(window_cube[k].a.y, window_cube[k].b.y), window_cube[k].c.y);
            int boundary_y_max = MAX(MAX(window_cube[k].a.y, window_cube[k].b.y), window_cube[k].c.y);

            for (int i = boundary_y_min; i <= boundary_y_max; i++) {
                for (int j = boundary_x_min; j <= boundary_x_max; j++) {
                    glm::vec3 barycentric = barycentric_coordinate(window_cube[k].a, window_cube[k].b, window_cube[k].c, glm::vec2(j, i));
                    if (barycentric.x >= 0 && barycentric.x <= 1 && barycentric.y >= 0 && barycentric.y <= 1 && barycentric.z >= 0 && barycentric.z <= 1) {
                        float z_interpolated = barycentric.x * window_cube[k].a.z + barycentric.y * window_cube[k].b.z + barycentric.z * window_cube[k].c.z;
                        
                        if (z_interpolated < z_buffer[i][j]) {       // this pixel will be displayed
                            
                                                                     // transform illuminant from world coordinate frame to triangle's object coordinate frame for shading
                            glm::vec4  direction = - *(obj_cube[k].p_object_frame_inv) * direction_directional;
                            
                            // update z-buffer
                            z_buffer[i][j] = z_interpolated;
                            
                            // interpolate to get pixel color, will be replaced by texture sampling
                            // glm::vec3 color_interpolated = barycentric.x * obj_cube[k].color_a + barycentric.y * obj_cube[k].color_b + barycentric.z * obj_cube[k].color_c;;
                            
                            // texture sampling, with perspective amendent
                            float w_n_inverse_a = 1 / clipping_cube[k].a.w;
                            float w_n_inverse_b = 1 / clipping_cube[k].b.w;
                            float w_n_inverse_c = 1 / clipping_cube[k].c.w;
                            float w_n_inverse_interpolated = barycentric.x * w_n_inverse_a + barycentric.y * w_n_inverse_b + barycentric.z * w_n_inverse_c;
                            glm::vec2 v_mul_ndc_w_inv_interpolated = barycentric.x * w_n_inverse_a * obj_cube[k].tex_coord_a + barycentric.y * w_n_inverse_b * obj_cube[k].tex_coord_b + barycentric.z * w_n_inverse_c * obj_cube[k].tex_coord_c;
                            glm::vec2 tex_coord_interpolated = v_mul_ndc_w_inv_interpolated / w_n_inverse_interpolated;
                            
                            tex_coord_interpolated.x = (int)tex_coord_interpolated.x;
                            tex_coord_interpolated.y = (int)tex_coord_interpolated.y;
                            cv::Vec3b color_fetched = texture_image.at<cv::Vec3b>(tex_coord_interpolated.y, tex_coord_interpolated.x);

                            // interpolate to get pixel normal vector
                            glm::vec4 normal_interpolated = barycentric.x * obj_cube[k].normal_a + barycentric.y * obj_cube[k].normal_b + barycentric.z * obj_cube[k].normal_c;
                            normal_interpolated = glm::normalize(normal_interpolated);  // normalize the vector interpolated
                            
                            // shade the pixel
                            glm::vec3 color_shaded = (radiance_ambient + MAX(glm::dot(direction, normal_interpolated),0) * radiance_directional) * glm::vec3(color_fetched[0],color_fetched[1],color_fetched[2]);
                            
                            // write to frame buffer
                            framebuffer_cv_mat.at<cv::Vec3b>(height - i, j) = cv::Vec3b(color_shaded.x, color_shaded.y, color_shaded.z);
                        }
                    }
                }
            }
        }

        // show img on screen
        cv::imshow(kWindowName, framebuffer_cv_mat);

    }

    return 0;
}

