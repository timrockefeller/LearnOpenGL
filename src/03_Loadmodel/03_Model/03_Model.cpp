#include <LOGL/Camera.h>
#include <LOGL/Common.h>
#include <LOGL/Glfw.h>
#include <LOGL/Model.h>
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
    static string title = "03_03 Model";
    Glfw::getInstance()->Init(DEFAULT_WIDTH, DEFAULT_HEIGHT, title);

    Shader* shader = new Shader("src/03_Loadmodel/03_Model/vertex.vs",
                                "src/03_Loadmodel/03_Model/frag_model.fs");

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    Model rmodel("assets/models/nanosuit/nanosuit.obj");

    glm::vec3 lightPos = glm::vec3(3.0f, 2.0f, 3.0f);

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

            shader->Use();

            shader->setMat4f("projection", projection);
            shader->setMat4f("view", view);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(
                model,
                glm::vec3(0.0f, -1.75f, 0.0f));  // translate it down so it's at
                                                 // the center of the scene
            model = glm::scale(
                model,
                glm::vec3(0.2f, 0.2f, 0.2f));  // it's a bit too big for our
                                               // scene, so scale it down
            shader->setMat4f("model", model);

            shader->setVec3f("viewPos", camera.GetPosition());
            shader->setVec3f("lightPos", lightPos);
            rmodel.Draw(*shader);
            shader->setMat4f("model", glm::translate(glm::mat4(1),lightPos));
            rmodel.Draw(*shader);
        } << Glfw::getInstance()->_endOp;
    Glfw::getInstance()->Run(&opList);

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
