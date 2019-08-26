#include <LOGL/Glfw.h>
#include <iostream>

using namespace LOGL;
using namespace KTKR;
using namespace std;

Glfw::Glfw()
    : window(NULL),
      _startOp([&]() {
          glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
      }),
      _endOp([&]() {
          glfwSwapBuffers(window);
          glfwPollEvents();
      }) {}
Glfw::~Glfw(){
    delete instance;
}
void Glfw::Init(size_t width, size_t height, const string& title) {
    /* init */
    glfwInit();
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* genWindow */
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        Terminate();
        return;
    }
    glfwMakeContextCurrent(window);

    /* Load GL */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl;
        Terminate();
        return;
    }
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, updateViewport);
}

void Glfw::CloseWindow() {
    glfwSetWindowShouldClose(window, true);
}
void Glfw::Terminate() {
    glfwTerminate();
}
GLFWwindow* Glfw::getWindow() {
    return window;
}

void Glfw::Run(OpQueue* opList) {
    while (opList->isHold() && !glfwWindowShouldClose(window)) {
        opList->Run();
        // TODO
    }
    Terminate();
    return;
}

Glfw* Glfw::getInstance() {
    return instance;
}
Glfw* Glfw::instance = new Glfw();

void Glfw::updateViewport(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
