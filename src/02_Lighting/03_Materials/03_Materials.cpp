#include <LOGL/Camera.h>
#include <LOGL/Common.h>
#include <LOGL/Glfw.h>
#include <LOGL/Shader.h>
#include <Util/EventListener.h>
#include <Util/GStorage.h>
#include <iostream>
using namespace LOGL;
using namespace KTKR;
using namespace std;

void processCameraInput(GLFWwindow* window, Camera* camera, float deltaTime);
int main(int argc, char const* argv[]) {
    static string title = "02_03 Material";
    Glfw::getInstance()->Init(DEFAULT_WIDTH, DEFAULT_HEIGHT, title);

    float vertices[] = {
        // with normal 6*36
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f, -0.5f,
        0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
        0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f,
        0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,

        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,
        0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,
        0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
        -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
        -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
        1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
        0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
        1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, -0.5f,
        0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
        0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,
        0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
        0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,
        0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f};
    unsigned int cubeVAO, VBO;
    {
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);
        glBindVertexArray(cubeVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    unsigned int lightVAO;
    {
        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);
        // 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
    }
    Shader* lightingShader =
        new Shader("./src/02_Lighting/03_Materials/vertex.vs",
                   "./src/02_Lighting/03_Materials/frag_lighting.fs");
    Shader* lampShader =
        new Shader("./src/02_Lighting/03_Materials/vertex.vs",
                   "./src/02_Lighting/03_Materials/frag_lamp.fs");
    lightingShader->setVec3f("material.ambient", 0.19225f, 0.19225f, 0.19225f);
    lightingShader->setVec3f("material.diffuse", 0.50754f, 0.50754f, 0.50754f);
    lightingShader->setVec3f("material.specular", 0.508273f, 0.508273f, 0.508273f);
    lightingShader->setFloat("material.shininess", 0.4f * 128);
    lightingShader->setVec3f("light.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader->setVec3f("light.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader->setVec3f("light.specular", 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // event
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
    glEnable(GL_DEPTH_TEST);
    // loop
    OpQueue opList;
    opList << [&]() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
           << Glfw::getInstance()->_startOp <<
        [&]() {
            processCameraInput(Glfw::getInstance()->getWindow(), &camera,
                               Glfw::getInstance()->deltaTime);
            // pass projection matrix to shader (note that in this case it could
            // change every frame)

            glm::mat4 projection = camera.GetProjectionMatrix();
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 model = glm::mat4(1.0f);

            lightingShader->Use();
            lightingShader->setMat4f("projection", projection);
            lightingShader->setMat4f("view", view);
            lightingShader->setMat4f("model", model);

            // lightingShader->setVec3f("objectColor", 1.0f, 0.5f, 0.31f);
            lightingShader->setVec3f("light.position", lightPos);
            lightingShader->setVec3f("viewPos", camera.GetPosition());

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // move light
            lightPos = glm::vec3(1.2f * glm::cos(glfwGetTime()), 1.0f,
                                2.0f * glm::sin(glfwGetTime()));
            // change color
            glm::vec3 lightColor;
            lightColor.x = sin(glfwGetTime() * 2.0f);
            lightColor.y = sin(glfwGetTime() * 0.7f);
            lightColor.z = sin(glfwGetTime() * 1.3f);
            glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);  // 降低影响
            glm::vec3 ambientColor =
                diffuseColor * glm::vec3(0.2f);  // 很低的影响
            lightingShader->setVec3f("light.ambient", ambientColor);
            lightingShader->setVec3f("light.diffuse", diffuseColor);

            lampShader->Use();
            // 设置模型、视图和投影矩阵uniform
            lampShader->setMat4f("projection", projection);
            lampShader->setMat4f("view", view);
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));
            lampShader->setMat4f("model", model);

            // 绘制灯立方体对象
            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        } << Glfw::getInstance()->_endOp;
    Glfw::getInstance()->Run(&opList);

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);

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
