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
    const string title = "04_06 Cube Map";
    Glfw::getInstance()->Init(DEFAULT_WIDTH, DEFAULT_HEIGHT, title);

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
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
    VAO cubeVAO(&(cubeVertices[0]), sizeof(cubeVertices), {3, 2});

    Texture skyboxTexture(
        {"assets/textures/skybox/right.jpg", "assets/textures/skybox/left.jpg",
         "assets/textures/skybox/top.jpg", "assets/textures/skybox/bottom.jpg",
         "assets/textures/skybox/front.jpg",
         "assets/textures/skybox/back.jpg"});
    Shader skyboxShader("src/04_Advanced/06_CubeMap/vertex_cm.vs",
                        "src/04_Advanced/06_CubeMap/frag_cm.fs");

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
        ->bind(EventListener::KEYBOARD_PRESS | GLFW_KEY_ESCAPE,
               [&]() { Glfw::getInstance()->CloseWindow(); });

    OpQueue* oplist = new OpQueue;
    (*oplist) << Glfw::getInstance()->_startOp << [&]() {
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.GetZoom()),
            (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT, 0.1f, 100.0f);
        skyboxShader.setMat4f("view", glm::mat4(glm::mat3(view)));
        skyboxShader.setMat4f("projection", projection);

        cubeVAO.Use();
        skyboxShader.setInt("skybox", 0);
        skyboxTexture.setUnit(0);
        cubeVAO.Draw();
    } << Glfw::getInstance()->_endOp;

    Glfw::getInstance()->Run(oplist);

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
