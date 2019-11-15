#include <LOGL/Camera.h>
#include <LOGL/Common.h>
#include <LOGL/FBO.h>
#include <LOGL/Glfw.h>
#include <LOGL/Shader.h>
#include <LOGL/Texture.h>
#include <LOGL/VAO.h>
#include <Util/EventListener.h>
#include <Util/GStorage.h>
#include <Util/OpQueue.h>
using namespace LOGL;
using namespace KTKR;
using namespace std;

void processCameraInput(GLFWwindow* window, Camera* camera, float deltaTime);
int main(int argc, char const* argv[]) {
    const string title = "04_05 Frame Buffer";
    Glfw::getInstance()->Init(DEFAULT_WIDTH, DEFAULT_HEIGHT, title);

    float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};
    float planeVertices[] = {
        5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, 5.0f,
        0.0f, 0.0f,  -5.0f, -0.5f, -5.0f, 0.0f,  2.0f,

        5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, -5.0f,
        0.0f, 2.0f,  5.0f,  -0.5f, -5.0f, 2.0f,  2.0f};
    float quadVertices[] = {-1.0f, 1.0f, 0.0f, 1.0f,   //
                            -1.0f, -1.0f, 0.0f, 0.0f,  //
                            1.0f, -1.0f, 1.0f, 0.0f,   //

                            // -1.0f, 1.0f,  0.0f, 1.0f,  //
                            // 1.0f,  -1.0f, 1.0f, 0.0f,  //
                            1.0f, 1.0f, 1.0f, 1.0f};
    unsigned int quadIndex[] = {0, 1, 2, 0, 2, 3};

    FBO fbor(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    fbor.Use();  // 在绑定到GL_FRAMEBUFFER目标之后，所有的读取和写入帧缓冲的操作将会影响当前绑定的帧缓冲。

    // cube VAO
    VAO cubeVAO(&(cubeVertices[0]), sizeof(cubeVertices), {3, 2});

    // plane VAO
    VAO planeVAO(planeVertices, sizeof(planeVertices), {3, 2});

    // screen quad VAO
    VAO quadVAO(&(quadVertices[0]), sizeof(quadVertices), {2, 2}, quadIndex, 6);

    Texture cubeTexture("./assets/textures/container2.png"),
        floorTexture("./assets/textures/metal.png");

    cubeTexture.setUnit(0);
    floorTexture.setUnit(1);

    fbor.GetTexture()->setUnit(2);

    Shader shader("./src/04_Advanced/05_FrameBuffer/vertex.vs",
                  "./src/04_Advanced/05_FrameBuffer/frag_color.fs"),
        screenshader("./src/04_Advanced/05_FrameBuffer/vertex_fb.vs",
                     "./src/04_Advanced/05_FrameBuffer/frag_fb.fs");
    shader.setInt("texture1", 0);
    screenshader.setInt("screenTexture", 2);
    screenshader.setInt("ctrl", 0);
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // event
    EventListener::getInstance()
        ->bind(EventListener::Event_Type::MOUSE_SCROLL,
               [&]() {
                   float* r =
                       GStorage<float>::getInstance()->getPtr(strMouseScrollY);
                   if (r)
                       camera.ProcessMouseScroll(*r);
               })
        ->bind(
            EventListener::Event_Type::MOUSE_MOVE,
            [&]() {
                float *xoffset =
                          GStorage<float>::getInstance()->getPtr(strMousePosX),
                      *yoffset =
                          GStorage<float>::getInstance()->getPtr(strMousePosY);
                if (xoffset && yoffset)
                    camera.ProcessMouseMovement(*xoffset, *yoffset);
            })
        ->bind(EventListener::KEYBOARD_PRESS | GLFW_KEY_0,
               [&]() { screenshader.setInt("ctrl", 0); })
        ->bind(EventListener::KEYBOARD_PRESS | GLFW_KEY_1,
               [&]() { screenshader.setInt("ctrl", 1); })
        ->bind(EventListener::KEYBOARD_PRESS | GLFW_KEY_2,
               [&]() { screenshader.setInt("ctrl", 2); })
        ->bind(EventListener::KEYBOARD_PRESS | GLFW_KEY_3,
               [&]() { screenshader.setInt("ctrl", 3); })
        ->bind(EventListener::KEYBOARD_PRESS | GLFW_KEY_4,
               [&]() { screenshader.setInt("ctrl", 4); });

    OpQueue op;
    op << Glfw::getInstance()->_startOp << [&]() {  // draw default scene
        processCameraInput(Glfw::getInstance()->getWindow(), &camera,
                           Glfw::getInstance()->deltaTime);

        /**
         *  render fbo scene
         *
         */
        fbor.Use();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.GetZoom()),
            (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT, 0.1f, 100.0f);
        shader.setMat4f("view", view);
        shader.setMat4f("projection", projection);
        // cubes
        shader.setInt("texture1", 0);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        shader.setMat4f("model", model);
        cubeVAO.Draw();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        shader.setMat4f("model", model);
        cubeVAO.Draw();
        // floor
        shader.setInt("texture1", 1);
        shader.setMat4f("model", glm::mat4(1.0f));
        planeVAO.Draw();
        // } << [&]() {
        /**
         *  render quad scene
         *
         */
        FBO::UseDefault();
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenshader.Use();
        fbor.GetTexture()->setUnit(2);
        quadVAO.Draw();
        // glBindVertexArray(quadVAO);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
    } << Glfw::getInstance()->_endOp;

    Glfw::getInstance()->Run(&op);

    // glDeleteVertexArrays(1, &planeVAO);
    // glDeleteVertexArrays(1, &cubeVAO);
    // glDeleteBuffers(1, &cubeVBO);
    // glDeleteBuffers(1, &planeVBO);

    return 0;
}
void processCameraInput(GLFWwindow* window, Camera* camera, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Glfw::getInstance()->CloseWindow();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(CAM_RIGHT, deltaTime);
}
