#include <LOGL/Common.h>
#include <LOGL/Glfw.h>
#include <Util/EventListener.h>
#include <Util/GStorage.h>
#include <iostream>

using namespace LOGL;
using namespace KTKR;
using namespace std;

Glfw::Glfw()
    : window(NULL),
      _startOp([&]() {
          //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
          glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
          float ct = (float)glfwGetTime();
          deltaTime = ct - lastTime;
          lastTime = ct;
      }),
      _endOp([&]() {
          glfwSwapBuffers(window);
          glfwPollEvents();
      }){}
Glfw::~Glfw() {
    // delete instance;
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

    // bind events
    glfwSetCursorPosCallback(
        window, [](GLFWwindow* window, double xpos, double ypos) {
            static float lastX = (float)xpos;
            static float lastY = (float)ypos;

            static float xoffset;
            static float yoffset;
            GStorage<float>::getInstance()->Register(strMousePosX, xoffset);
            GStorage<float>::getInstance()->Register(strMousePosY, yoffset);
            xoffset = (float)xpos - lastX;
            yoffset = lastY - (float)ypos;
            lastX = (float)xpos;
            lastY = (float)ypos;
            EventListener::getInstance()->response(
                EventListener::Event_Type::MOUSE_MOVE);
        });
    glfwSetScrollCallback(
        window, [](GLFWwindow* window, double xoffset, double yoffset) {
            GStorage<float>::getInstance()->Register(strMouseScrollX,
                                                     (float)xoffset);
            GStorage<float>::getInstance()->Register(strMouseScrollY,
                                                     (float)yoffset);
            EventListener::getInstance()->response(
                EventListener::Event_Type::MOUSE_SCROLL);
        });
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scanCode,
                                  int state, int mods) {
        size_t kbState =
            (state == GLFW_PRESS ? EventListener::KEYBOARD_PRESS
                                 : (state == GLFW_REPEAT
                                        ? EventListener::KEYBOARD_REPEAT
                                        : (state == GLFW_RELEASE
                                               ? EventListener::KEYBOARD_RELEASE
                                               : 0)));
        if (kbState != 0)
            EventListener::getInstance()->response(key | kbState);
        EventListener::getInstance()->response(key | EventListener::KEYBOARD);
    });

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

void Glfw::Run(OpQueue* opList){
    Run(OpQueue::toPtr(opList));
}

void Glfw::Run(Ptr<OpQueue> &opList) {
    while (opList!=NULL && !glfwWindowShouldClose(window)) {
		if (opList->isHold()) 
			opList->Run();
	}
    Terminate();
}

// Glfw* Glfw::getInstance() {
//     return instance;
// }
// Glfw* Glfw::instance = new Glfw();

void Glfw::updateViewport(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    EventListener::getInstance()->response(EventListener::WINDOW_ZOOM);
}
