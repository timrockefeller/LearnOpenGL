#include <LOGL/Camera.h>
#include <LOGL/Common.h>
#include <LOGL/Glfw.h>
#include <LOGL/Shader.h>
#include <LOGL/Texture.h>
#include <Util/EventListener.h>
#include <Util/GStorage.h>
#include <iostream>
using namespace LOGL;
using namespace KTKR;
using namespace std;

void processCameraInput(GLFWwindow* window, Camera* camera, float deltaTime);
int main(int argc, char const* argv[]) {
    static string title = "02_06 Multiple Lights";
    Glfw::getInstance()->Init(DEFAULT_WIDTH, DEFAULT_HEIGHT, title);

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  //
        0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,  //
        0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,  //
        0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,  //
        -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  //

        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  //
        0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  //
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  //
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  //
        -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  //
        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  //

        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  //
        -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  //
        -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  //
        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  //

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  //
        0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  //
        0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  //
        0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  //
        0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  //
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  //

        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,  //
        0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,  //
        0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,  //
        0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,  //
        -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 0.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,  //

        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  //
        0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  //
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  //
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  //
        -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  //
        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f   //
    };
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};
    unsigned int cubeVAO, VBO;
    {
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);
        glBindVertexArray(cubeVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    unsigned int lightVAO;
    {
        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);
        // 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
    }
    Texture tex_deffuse("./assets/textures/container2.png"),
        tex_specular("./assets/textures/container2_specular.png");
    Shader *lightingShader = new Shader(
               "./src/02_Lighting/06_MultipleLight/vertex.vs",
               "./src/02_Lighting/06_MultipleLight/frag_lighting.fs"),
           *lampShader =
               new Shader("./src/02_Lighting/06_MultipleLight/vertex.vs",
                          "./src/02_Lighting/06_MultipleLight/frag_lamp.fs");

    lightingShader->setInt("material.diffuse", 0);
    lightingShader->setInt("material.specular", 1);
    lightingShader->setFloat("material.shininess", 0.4f * 128);

    lightingShader->setVec3f("directlight.direction", -0.2f, -1.0f, -0.3f);
    lightingShader->setVec3f("directlight.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader->setVec3f("directlight.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader->setVec3f("directlight.specular", 1.0f, 1.0f, 1.0f);

    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.0f, 0.0f, -3.0f)};

    for (int i = 0; i < 4; i++) {
        lightingShader->setVec3f(
            (string) "pointLights[" + to_string(i) + "].ambient", 0.2f, 0.2f,
            0.2f);
        lightingShader->setVec3f(
            (string) "pointLights[" + to_string(i) + "].diffuse", 0.5f, 0.5f,
            0.5f);
        lightingShader->setVec3f(
            (string) "pointLights[" + to_string(i) + "].specular", 1.0f, 1.0f,
            1.0f);

        lightingShader->setFloat(
            (string) "pointLights[" + to_string(i) + "].constant", 1.0f);
        lightingShader->setFloat(
            (string) "pointLights[" + to_string(i) + "].linear", 0.09f);
        lightingShader->setFloat(
            (string) "pointLights[" + to_string(i) + "].quadratic", 0.032f);
        lightingShader->setVec3f(
            (string) "pointLights[" + to_string(i) + "].position",
            pointLightPositions[i]);
    }

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    lightingShader->setVec3f("spotLight.position", camera.GetPosition());
    lightingShader->setVec3f("spotLight.direction", camera.GetFront());
    lightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    lightingShader->setFloat("spotLight.outerCutOff",
                             glm::cos(glm::radians(17.5f)));
    lightingShader->setVec3f("spotLight.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader->setVec3f("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader->setVec3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
    
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

            glm::mat4 projection = camera.GetProjectionMatrix();
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 model = glm::mat4(1.0f);

            // // change color
            // glm::vec3 lightColor;
            // lightColor.x = sin(glfwGetTime() * 2.0f);
            // lightColor.y = sin(glfwGetTime() * 0.7f);
            // lightColor.z = sin(glfwGetTime() * 1.3f);
            // glm::vec3 diffuseColor = lightColor * glm::vec3(.5f);  //降低影响
            // glm::vec3 ambientColor =
            //     diffuseColor * glm::vec3(.2f);  // 很低的影响

            lightingShader->Use();
            lightingShader->setMat4f("projection", projection);
            lightingShader->setMat4f("view", view);
            // directShader->setVec3f("light.ambient", ambientColor);
            // directShader->setVec3f("light.diffuse", diffuseColor);

            {  // for spot light update
                lightingShader->setVec3f("spotLight.position", camera.GetPosition());
                lightingShader->setVec3f("spotLight.direction", camera.GetFront());
            }

            lightingShader->setVec3f("viewPos", camera.GetPosition());
            glBindVertexArray(cubeVAO);
            tex_deffuse.setUnit(0);
            tex_specular.setUnit(1);
            for (unsigned int i = 0; i < 10; i++) {
                model = glm::translate(glm::mat4(1.f), cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle),
                                    glm::vec3(1.0f, 0.3f, 0.5f));
                lightingShader->setMat4f("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            lampShader->Use();
            lampShader->setMat4f("projection", projection);
            lampShader->setMat4f("view", view);
            for (int i = 0; i < 4; i++) {
                model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f));
                lampShader->setMat4f("model", model);
                glBindVertexArray(lightVAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
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
