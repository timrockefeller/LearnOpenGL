#include <LOGL/Camera.h>
#include <LOGL/Common.h>
#include <LOGL/Glfw.h>
#include <LOGL/Shader.h>
#include <LOGL/Texture.h>
#include <Util/EventListener.h>
#include <Util/GStorage.h>
#include <Util/OpQueue.h>
using namespace LOGL;
using namespace KTKR;
using namespace std;

void processCameraInput(GLFWwindow* window, Camera* camera, float deltaTime);
int main(int argc, char const* argv[]) {
    const string title = "04_01 Depth testing";
    Glfw::getInstance()->Init(DEFAULT_WIDTH, DEFAULT_HEIGHT, title);

    float cubeVertices[] = {
        // positions          // texture Coords
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
        // positions          // texture Coords (note we set these higher than 1
        // (together with GL_REPEAT as texture wrapping mode). this will cause
        // the floor texture to repeat)
        5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, 5.0f,
        0.0f, 0.0f,  -5.0f, -0.5f, -5.0f, 0.0f,  2.0f,

        5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, -5.0f,
        0.0f, 2.0f,  5.0f,  -0.5f, -5.0f, 2.0f,  2.0f};
    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    // plane VAO
    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    Texture cubeTexture("./assets/textures/marble.jpg"),
        floorTexture("./assets/textures/metal.png");

    cubeTexture.setUnit(0);
    floorTexture.setUnit(1);

    Shader shader("./src/04_Advanced/01_DepthTesting/vertex.vs",
                  "./src/04_Advanced/01_DepthTesting/frag_depth.fs");

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
        ->bind(EventListener::Event_Type::MOUSE_MOVE, [&]() {
            float *xoffset =
                      GStorage<float>::getInstance()->getPtr(strMousePosX),
                  *yoffset =
                      GStorage<float>::getInstance()->getPtr(strMousePosY);
            if (xoffset && yoffset)
                camera.ProcessMouseMovement(*xoffset, *yoffset);
        });

    ///////////////
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    ///////////////
    /**
        | 函数        | 描述                                         |
        | :---------- | :------------------------------------------- |
        | GL_ALWAYS   | 永远通过深度测试                             |
        | GL_NEVER    | 永远不通过深度测试                           |
        | GL_LESS     | 在片段深度值小于缓冲的深度值时通过测试       |
        | GL_EQUAL    | 在片段深度值等于缓冲区的深度值时通过测试     |
        | GL_LEQUAL   | 在片段深度值小于等于缓冲区的深度值时通过测试 |
        | GL_GREATER  | 在片段深度值大于缓冲区的深度值时通过测试     |
        | GL_NOTEQUAL | 在片段深度值不等于缓冲区的深度值时通过测试   |
        | GL_GEQUAL   | 在片段深度值大于等于缓冲区的深度值时通过测试 |
    */

    OpQueue op;
    op << Glfw::getInstance()->_startOp << [&]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processCameraInput(Glfw::getInstance()->getWindow(), &camera,
                           Glfw::getInstance()->deltaTime);
        shader.Use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.GetZoom()),
            (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT, 0.1f, 100.0f);
        shader.setMat4f("view", view);
        shader.setMat4f("projection", projection);
        // cubes
        glBindVertexArray(cubeVAO);
        shader.setInt("texture1", 0);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        shader.setMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        shader.setMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // floor
        glBindVertexArray(planeVAO);
        shader.setInt("texture1", 1);
        shader.setMat4f("model", glm::mat4(1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    } << Glfw::getInstance()->_endOp;

    Glfw::getInstance()->Run(&op);

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
