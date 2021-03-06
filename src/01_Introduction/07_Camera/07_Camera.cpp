#include <LOGL/Camera.h>
#include <LOGL/Common.h>
#include <LOGL/Glfw.h>
#include <LOGL/Shader.h>
#include <LOGL/Texture.h>
#include <Util/EventListener.h>
#include <Util/GStorage.h>
using namespace KTKR;
using namespace LOGL;
using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// timing
float deltaTime = 0.0f;  // time between current frame and last frame
float lastFrame = 0.0f;

int main(int argc, char const* argv[]) {
    const string title = "01_07: Camera";
    Glfw::getInstance()->Init(SCR_WIDTH, SCR_HEIGHT, title);

    // glfwSetCursorPosCallback(Glfw::getInstance()->getWindow(),
    // mouse_callback);
    // glfwSetScrollCallback(Glfw::getInstance()->getWindow(), scroll_callback);

    // objects
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  //
        0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,  //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,  //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,  //
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  //

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,  //
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,  //
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  //
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  //
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f,  //
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,  //

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,  //
        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,  //
        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,  //

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,  //
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,  //
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,  //
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f,  //
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  //

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,  //
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,  //
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,  //
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f,  //
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,  //
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  //
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  //
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f,  //
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f   //
    };

    unsigned int VAO, VBO;
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                              (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    // textures
    Texture texture1("assets/textures/container.jpg"),
        texture2("assets/textures/awesomeface.png", true);

    texture1.setUnit(0);
    texture2.setUnit(1);
    // shaders
    Shader* shader =
        new Shader("src/01_Introduction/06_Coordinate/vertex.vs",
                   "src/01_Introduction/06_Coordinate/frag_texture.fs");
    shader->Use();
    shader->Use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);

    // coordinate
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    glEnable(GL_DEPTH_TEST);
    camera.EnableFPS();

    // event
    EventListener::getInstance()
        ->bind(EventListener::Event_Type::MOUSE_SCROLL,
               []() {
                   float* r =
                       GStorage<float>::getInstance()->getPtr(strMouseScrollY);
                   if (r)
                       camera.ProcessMouseScroll(*r);
               })
        ->bind(
            EventListener::Event_Type::MOUSE_MOVE,
            []() {
                float *xoffset =
                          GStorage<float>::getInstance()->getPtr(strMousePosX),
                      *yoffset =
                          GStorage<float>::getInstance()->getPtr(strMousePosY);
                if (xoffset && yoffset)
                    camera.ProcessMouseMovement(*xoffset, *yoffset);
            })
        ->bind(EventListener::KEYBOARD_PRESS | GLFW_KEY_ESCAPE,
               []() { Glfw::getInstance()->CloseWindow(); })
        ->bind(EventListener::KEYBOARD | GLFW_KEY_W,
               []() { camera.ProcessKeyboard(CAM_FORWARD); })
        ->bind(EventListener::KEYBOARD | GLFW_KEY_S,
               []() { camera.ProcessKeyboard(CAM_BACKWARD); })
        ->bind(EventListener::KEYBOARD | GLFW_KEY_A,
               []() { camera.ProcessKeyboard(CAM_LEFT); })
        ->bind(EventListener::KEYBOARD | GLFW_KEY_D,
               []() { camera.ProcessKeyboard(CAM_RIGHT); });

    // loop
    OpQueue opList;
    opList << [&]() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
           << Glfw::getInstance()->_startOp <<
        [&]() {
            // per-frame time logic
            // --------------------

            // pass projection matrix to shader (note that in this case it could
            // change every frame)
            glm::mat4 projection = camera.GetProjectionMatrix();
            shader->setMat4f("projection", projection);
            // camera/view transformation
            glm::mat4 view = camera.GetViewMatrix();
            shader->setMat4f("view", view);

            glBindVertexArray(VAO);
            for (unsigned int i = 0; i < 10; i++) {
                glm::mat4 model = glm::mat4(1);
                model = glm::translate(model, cubePositions[i]);
                float angle = (i % 3 == 0 ? (float)glfwGetTime() : 1.0f) *
                              20.0f * (i + 1);
                model = glm::rotate(model, glm::radians(angle),
                                    glm::vec3(1.0f, 0.3f, 0.5f));
                shader->setMat4f("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        } << Glfw::getInstance()->_endOp;
    Glfw::getInstance()->Run(&opList);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    return 0;
}
