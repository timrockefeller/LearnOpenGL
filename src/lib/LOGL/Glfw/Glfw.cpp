#include <LOGL/Glfw.h>
#include<iostream>


using namespace LOGL;
using namespace KTKR;
using namespace std;

Glfw::Glfw() : window(NULL) {}

void Glfw::Init(size_t width,
                size_t height,
                const string& title) {
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
    glViewport(0, 0, 800, 600);
}


void Glfw::CloseWindow() { glfwSetWindowShouldClose(window, true); }
void Glfw::Terminate() { glfwTerminate(); }


void Glfw::Run(OpQueue *opList){
    while(opList->isHold()){
        opList->Run();
    }
    CloseWindow();
    Terminate();
}






Glfw* Glfw::getInstance(){
    return instance;
}
Glfw* Glfw::instance = new Glfw();
