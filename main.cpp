#include <opencv2/opencv.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cube.h"
#include "rasterizer.h"

#define height  512
#define width  512
using namespace sora;
using namespace glm;


int main(int argc, char const* argv[]) {

    // create framebuffer
    static const char kWindowName[] = "sora";
    cv::Mat framebuffer_cv_mat = cv::Mat::zeros(height, width, CV_8UC3);

    // load texture image
    cv::Mat texture_image = cv::imread(Cube::getTexturePath());
    if (texture_image.empty()) {
        std::cout << "texture image load failure\n";
        return -1;
    }
    int texture_width = texture_image.cols;
    int texture_height = texture_image.rows;
    if (texture_width != Cube::_width || texture_height != Cube::_height) {
        std::cout << "texture image size not matched\n";
        return -2;
    }

    // create window
    cv::namedWindow(kWindowName, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);
    cv::resizeWindow(kWindowName, cv::Size(width, height));
    cv::setWindowTitle(kWindowName, kWindowName);

    //initialize camera coordinate frame
    mat4 cameraCoordinateFrame = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 1, 1
    );
    mat4 cameraFrameInv = inverse(cameraCoordinateFrame);

    //initialize object coordinate frame with respect to world coordinate frame
    mat4 objectCoordinateFrame(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, -3, 1
    );
    mat4 objectFrameInv = inverse(objectCoordinateFrame);

    Cube cube = Cube::getInstance();
    auto colorBufferWriter = [&framebuffer_cv_mat, &texture_image](int X, int Y, int textCoorU, int textCoorV, float illuminant) {
        cv::Vec3b colorFetched = texture_image.at<cv::Vec3b>(textCoorU, textCoorV);
        framebuffer_cv_mat.at<cv::Vec3b>(X, Y) = illuminant * colorFetched;
    };
    
    Rasterizer rasterizer(  cube._vertice, 
                            cube._tris, 
                            cameraCoordinateFrame, 
                            objectCoordinateFrame, 
                            width, height,
                            colorBufferWriter
                            );
    
    //--------------------------------- matrix for view rotation in object coordinate frame ---------------------------------

    // rotation matrix provoked by key event
    const float rot_angle = radians(15.f);
    mat4 mat_rot_y = rotate(mat4(1), rot_angle, vec3(0, 1, 0));
    mat4 mat_rot_y_inv = inverse(mat_rot_y);
    mat4 mat_rot_x = rotate(mat4(1), rot_angle, vec3(1, 0, 0));
    mat4 mat_rot_x_inv = inverse(mat_rot_x);

    //-----------------------------------------------------------------------------------------------------------------------
    

    //----------------------------------------- render loop ------------------------------------------------------------
    while (true) {

        // clear frame buffer
        framebuffer_cv_mat = cv::Mat::zeros(height, width, CV_8UC3);
        // handle key events
        int key = cv::waitKey(100);
        if (key == 'q') {
            cv::destroyWindow(kWindowName);
            break;
        }
        switch (key) {
        case 'd':
            cameraCoordinateFrame = objectCoordinateFrame * mat_rot_y_inv * objectFrameInv* cameraCoordinateFrame;
            cameraFrameInv = inverse(cameraCoordinateFrame);
            break;
        case 'a':
            cameraCoordinateFrame = objectCoordinateFrame* mat_rot_y * objectFrameInv* cameraCoordinateFrame;
            cameraFrameInv= inverse(cameraCoordinateFrame);
            break;
        case 's':
            cameraCoordinateFrame = objectCoordinateFrame * mat_rot_x * objectFrameInv* cameraCoordinateFrame;
            cameraFrameInv = inverse(cameraCoordinateFrame);
            break;
        case 'w':
            cameraCoordinateFrame= objectCoordinateFrame * mat_rot_x_inv * objectFrameInv * cameraCoordinateFrame;
            cameraFrameInv = inverse(cameraCoordinateFrame);
            break;
        }
        rasterizer.setCameraFrame(cameraCoordinateFrame);
        rasterizer.rasterize();
        // show img on screen
        cv::imshow(kWindowName, framebuffer_cv_mat);

    }

    return 0;
}

