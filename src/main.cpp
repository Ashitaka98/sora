#include <GL/glut.h>

#include "primitiveFactory.h"
#include "rasterizer.h"

using namespace sora;
#define WindowHeight  512
#define WindowWidth  512

const int FrameBufferSize = WindowWidth * WindowHeight * 3;
GLubyte FrameBuffer[FrameBufferSize];

//initialize camera coordinate frame
mat4 cameraCoordinateFrame = mat4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 1, 1
);
mat4 cameraFrameInv = glm::inverse(cameraCoordinateFrame);

//initialize object coordinate frame with respect to world coordinate frame
mat4 objectCoordinateFrame(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, -5, 1
);
mat4 objectFrameInv = glm::inverse(objectCoordinateFrame);

Rasterizer* raster;

void processKeyboardInterrupt(unsigned char key, int x, int y) {
    //--------------------------------- matrix for view rotation in object coordinate frame ---------------------------------
    // rotation matrix provoked by key event
    static mat4 mat_rot_y = Camera::GetRotateMatrixY(15);
    static mat4 mat_rot_y_inv = glm::inverse(mat_rot_y);
    static mat4 mat_rot_x = Camera::GetRotateMatrixX(15);
    static mat4 mat_rot_x_inv = glm::inverse(mat_rot_x);
    // clear frame buffer
    memset(FrameBuffer, 0, FrameBufferSize);
    // handle key events
    switch (key) {
    case 'd':
        raster->GetCamera()->RotateAroundLookat(mat_rot_y_inv, objectCoordinateFrame);
        break;
    case 'a':
        raster->GetCamera()->RotateAroundLookat(mat_rot_y, objectCoordinateFrame);
        break;
    case 's':
        raster->GetCamera()->RotateAroundLookat(mat_rot_x, objectCoordinateFrame);
        break;
    case 'w':
        raster->GetCamera()->RotateAroundLookat(mat_rot_x_inv, objectCoordinateFrame);
        break;
    }
    raster->ClearDepthBuffer();
    raster->Rasterize();
    glutPostRedisplay();
};

void display(void)
{
    raster->ClearDepthBuffer();
    raster->Rasterize();
    glDrawPixels(WindowWidth, WindowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, FrameBuffer);
    glutSwapBuffers();
}

int main(int argc, char* argv[]) {


    raster = new Rasterizer(WindowWidth, WindowHeight);
    auto texture = std::make_shared<Texture>("../res/checkboard.jpg");
    auto camera = std::make_shared<Camera>(cameraCoordinateFrame, 90);
    auto light = std::make_shared<Illuminare>(IlluminareType::Directional, 0.5f, glm::normalize(vec3(-1, -1, -1)));

    std::vector<uint8> vb;
    std::vector<uint8> ib;
    uint32 primitives = 0;
    VertexStreamLayout layout;
    layout.AddVertexChannelLayout(VertexChannel::Position, VertexFormat::Float4);
    layout.AddVertexChannelLayout(VertexChannel::Normal, VertexFormat::Float3);
    layout.AddVertexChannelLayout(VertexChannel::TexCoord, VertexFormat::Float2);

    Plane::GetInstance(vb, ib, layout, primitives);
    Cube::GetInstance(vb,ib,layout,primitives);
    auto colorBufferWriter = [&framebuffer = FrameBuffer](int X, int Y, ubvec3 color) {
        framebuffer[3 * WindowWidth * Y + 3 * X] = color.b;
        framebuffer[3 * WindowWidth * Y + 3 * X + 1] = color.g;
        framebuffer[3 * WindowWidth * Y + 3 * X + 2] = color.r;

    };
    raster->SetAmbientRadiance(0.5);
    raster->EnableAmbient(true);
    raster->SetCamera(camera);
    raster->SetIlluminare(light);
    raster->SetTexture(texture);
    raster->SetObjectCoordFrame(objectCoordinateFrame);
    raster->SetWriter(colorBufferWriter);
    raster->SetData(vb.data(), vb.size(), ib.data(), ib.size(), primitives, layout);
    
    raster->ClearDepthBuffer();
    raster->Rasterize();
    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutCreateWindow("SORA");
    glutDisplayFunc(&display);
    glutKeyboardFunc(&processKeyboardInterrupt);
    glutMainLoop();
    
    delete raster;
    return 0;
}

