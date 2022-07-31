#include <GL/glut.h>

#include "primitiveFactory.h"
#include "renderController.h"

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

//initialize object coordinate frame with respect to world coordinate frame
mat4 objectCoordinateFrame(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, -5, 1
);

RenderController render(WindowWidth, WindowHeight);

void processKeyboardInterrupt(unsigned char key, int x, int y) {
    //--------------------------------- matrix for view rotation in object coordinate frame ---------------------------------
    // rotation matrix provoked by key event
    static mat4 mat_rot_y = Camera::GetRotateMatrixY(15);
    static mat4 mat_rot_y_inv = glm::inverse(mat_rot_y);
    static mat4 mat_rot_x = Camera::GetRotateMatrixX(15);
    static mat4 mat_rot_x_inv = glm::inverse(mat_rot_x);
    static int mode = 0;
    // clear frame buffer
    memset(FrameBuffer, 0, FrameBufferSize);
    // handle key events
    switch (key) {
    case 'd':
        render.GetCamera()->RotateAroundLookat(mat_rot_y_inv, objectCoordinateFrame);
        break;
    case 'a':
        render.GetCamera()->RotateAroundLookat(mat_rot_y, objectCoordinateFrame);
        break;
    case 's':
        render.GetCamera()->RotateAroundLookat(mat_rot_x, objectCoordinateFrame);
        break;
    case 'w':
        render.GetCamera()->RotateAroundLookat(mat_rot_x_inv, objectCoordinateFrame);
        break;
    case 'm':
        switch (mode)
        {
        case 0:
            render.EnableVisualizeDepthBuffer(true);
            mode = 1;
            break;
        case 1:
            render.EnableVisualizeDepthBuffer(false);
            render.EnableVisualizeShadowMap(true);
            mode = 2;
            break;
        case 2:
            render.EnableVisualizeShadowMap(false);
            mode = 0;
            break;
        default:
            break;
        }
    }
    render.Render();
    glutPostRedisplay();
};

void display(void)
{
    render.Render();
    glDrawPixels(WindowWidth, WindowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, FrameBuffer);
    glutSwapBuffers();
}

int main(int argc, char* argv[]) {

    auto texture_cube = std::make_shared<Texture>("../res/checkboard.jpg");
    auto texture_plane = std::make_shared<Texture>("../res/marbel.jpg");
    auto camera = std::make_shared<Camera>(cameraCoordinateFrame,ProjectionType::Perspective,90,0,WindowHeight/WindowWidth,1,9);
    auto light = std::make_shared<Illuminare>(IlluminareType::Directional, 0.5f, glm::normalize(vec3(1, 1, 1)));

    std::vector<uint8> vb1;
    std::vector<uint8> ib1;
    uint32 primitives1 = 0;
    VertexStreamLayout layout1;
    layout1.AddVertexChannelLayout(VertexChannel::Position, VertexFormat::Float4);
    layout1.AddVertexChannelLayout(VertexChannel::Normal, VertexFormat::Float3);
    layout1.AddVertexChannelLayout(VertexChannel::TexCoord, VertexFormat::Float2);

    std::vector<uint8> vb2;
    std::vector<uint8> ib2;
    uint32 primitives2 = 0;
    VertexStreamLayout layout2;
    layout2.AddVertexChannelLayout(VertexChannel::Position, VertexFormat::Float4);
    layout2.AddVertexChannelLayout(VertexChannel::Normal, VertexFormat::Float3);
    layout2.AddVertexChannelLayout(VertexChannel::TexCoord, VertexFormat::Float2);

    Plane::CreateInstance(vb1, ib1, layout1, primitives1);
    Cube::CreateInstance(vb2,ib2,layout2,primitives2);
    DrawCallData data1(vb1.data(), vb1.size(), ib1.data(), ib1.size(), primitives1, layout1);
    DrawCallData data2(vb2.data(), vb2.size(), ib2.data(), ib2.size(), primitives2, layout2);
    auto colorBufferWriter = [&framebuffer = FrameBuffer](int X, int Y, ubvec3 color) {
        framebuffer[3 * WindowWidth * Y + 3 * X] = color.b;
        framebuffer[3 * WindowWidth * Y + 3 * X + 1] = color.g;
        framebuffer[3 * WindowWidth * Y + 3 * X + 2] = color.r;
    };

    render.AddDrawCall(data1, objectCoordinateFrame, texture_cube, true, true, true, true, 0.5f);
    render.AddDrawCall(data2, objectCoordinateFrame, texture_plane, true, true, true, true, 0.5f);
    render.SetCamera(camera);
    render.SetIlluminare(light); 
    render.SetWriter(colorBufferWriter);
    render.Render();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutCreateWindow("SORA");
    glutDisplayFunc(&display);
    glutKeyboardFunc(&processKeyboardInterrupt);
    glutMainLoop();
    
    return 0;
}

