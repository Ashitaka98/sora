#include <opencv2/opencv.hpp>
#include "transformations.h"
#include "triangle.h"
#include "utilities.h"

// camera coordinate frame transformation_matrix with respect to world coordinate
glm::mat4 camera_coordinate_frame(0);
glm::mat4 camera_frame_inv;

// mouse event handler
//void onMouseEvent(int event, int x, int y, int flag, void* ustc);

int main(int argc, char const* argv[]) {
    //initialize window and camera parameters
    int width = 512;
    int height = 512;
    float aspect_ratio = height / width;
    const float field_of_view = glm::radians(90.f);
    float near = 1;
    float far = 2;
    float shift_x = 0;
    float shift_y = 0;

    // create framebuffer
    static const char kWindowName[] = "sora";
    cv::Mat framebuffer_cv_mat = cv::Mat::zeros(height, width, CV_8UC3);

    // initialize window
    cv::namedWindow(kWindowName, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);
    cv::resizeWindow(kWindowName, cv::Size(width, height));
    cv::setWindowTitle(kWindowName, kWindowName);
    //cv::setMouseCallback(kWindowName, onMouseEvent,(void*)&camera_coordinate_frame);
    
    //initialize camera coordinate system
    camera_coordinate_frame[0][0] = 1;
    camera_coordinate_frame[1][1] = 1;
    camera_coordinate_frame[2][2] = 1;
    camera_coordinate_frame[3][2] = 1;
    camera_coordinate_frame[3][3] = 1;
    camera_frame_inv = glm::inverse(camera_coordinate_frame);

    // initialize object
    Triangle obj_coordinate_tri;    // default constructor


    // rotation matrix for camera provoked by key event
    const float rot_angle = glm::radians(15.f);
    glm::mat4 mat_rot_y = glm::rotate(glm::mat4(1), rot_angle, glm::vec3(0, 1, 0));
    glm::mat4 mat_rot_y_inv = glm::inverse(mat_rot_y);
    glm::mat4 mat_rot_x = glm::rotate(glm::mat4(1), rot_angle, glm::vec3(1, 0, 0));
    glm::mat4 mat_rot_x_inv = glm::inverse(mat_rot_x);
    // render loop
    while (true) {
        
        // clear the buffer
        framebuffer_cv_mat = cv::Mat::zeros(height, width, CV_8UC3);

        // handle key events
        int key = cv::waitKey(100);
        if (key == 'q') {
            cv::destroyWindow(kWindowName);
            break;
        }
        switch (key) {
        case 'd':
            camera_coordinate_frame = obj_coordinate_tri.object_coordinate_frame * mat_rot_y_inv * obj_coordinate_tri.object_frame_inv * camera_coordinate_frame;
            camera_frame_inv = glm::inverse(camera_coordinate_frame);
            break;
        case 'a':
            camera_coordinate_frame = obj_coordinate_tri.object_coordinate_frame * mat_rot_y * obj_coordinate_tri.object_frame_inv * camera_coordinate_frame;
            camera_frame_inv = glm::inverse(camera_coordinate_frame);
            break;
        case 's':
            camera_coordinate_frame = obj_coordinate_tri.object_coordinate_frame * mat_rot_x * obj_coordinate_tri.object_frame_inv * camera_coordinate_frame;
            camera_frame_inv = glm::inverse(camera_coordinate_frame);
            break;
        case 'w':
            camera_coordinate_frame = obj_coordinate_tri.object_coordinate_frame * mat_rot_x_inv * obj_coordinate_tri.object_frame_inv * camera_coordinate_frame;
            camera_frame_inv = glm::inverse(camera_coordinate_frame);
            break;
        }

        // actual rendering should happen here!
        // TODO: render

        // convert object coordinate to camera coordinate
        Triangle world_coordinate_tri = obj_coordinate_tri.obj2world();
        Triangle cam_coordinate_tri = world_coordinate_tri.world2cam();

        // perspective projection
        glm::mat4 perspective_matrix = matrix_PerspectiveProjection(field_of_view, aspect_ratio, glm::vec2(shift_x,shift_y), near, far);
        Triangle clipping_coordinate_tri;
        clipping_coordinate_tri.a = perspective_matrix * cam_coordinate_tri.a;
        clipping_coordinate_tri.b = perspective_matrix * cam_coordinate_tri.b;
        clipping_coordinate_tri.c = perspective_matrix * cam_coordinate_tri.c;

        // clipping

        // NDC coordinate
        Triangle NDC_coordinate_tri;
        NDC_coordinate_tri.a = clipping_coordinate_tri.a / clipping_coordinate_tri.a[3];
        NDC_coordinate_tri.b = clipping_coordinate_tri.b / clipping_coordinate_tri.b[3];
        NDC_coordinate_tri.c = clipping_coordinate_tri.c / clipping_coordinate_tri.c[3];

        // backface culling

        // viewport transform
        glm::mat4 viewport_matrix = matrix_viewportTransform(width, height);
        Triangle window_coordinate_tri;
        window_coordinate_tri.a = viewport_matrix * NDC_coordinate_tri.a;
        window_coordinate_tri.b = viewport_matrix * NDC_coordinate_tri.b;
        window_coordinate_tri.c = viewport_matrix * NDC_coordinate_tri.c;
        
        // rasterization
        cv::Vec3b red(0, 0, 255);
        int boundary_x_min = MIN(MIN(window_coordinate_tri.a.x, window_coordinate_tri.b.x), window_coordinate_tri.c.x);
        int boundary_x_max = MAX(MAX(window_coordinate_tri.a.x, window_coordinate_tri.b.x), window_coordinate_tri.c.x);
        int boundary_y_min = MIN(MIN(window_coordinate_tri.a.y, window_coordinate_tri.b.y), window_coordinate_tri.c.y);
        int boundary_y_max = MAX(MAX(window_coordinate_tri.a.y, window_coordinate_tri.b.y), window_coordinate_tri.c.y);

        for (int i = boundary_y_min; i <= boundary_y_max; i++) {
            for (int j = boundary_x_min; j <= boundary_x_max; j++) {
                glm::vec3 barycentric = barycentric_coordinate(window_coordinate_tri.a,window_coordinate_tri.b,window_coordinate_tri.c, glm::vec2(j, i));
                if (barycentric.x >= 0 && barycentric.x <= 1 && barycentric.y >= 0 && barycentric.y <= 1 && barycentric.z >= 0 && barycentric.z <= 1) {
                    glm::vec3 color_interpolated = barycentric.x * window_coordinate_tri.color_a + barycentric.y * window_coordinate_tri.color_b + barycentric.z * window_coordinate_tri.color_c;;
                    framebuffer_cv_mat.at<cv::Vec3b>(height - i, j) = cv::Vec3b(color_interpolated.x, color_interpolated.y, color_interpolated.z);
                }
            }
        }
        // show img on screen
        cv::imshow(kWindowName, framebuffer_cv_mat);
        
    }

    return 0;
}

