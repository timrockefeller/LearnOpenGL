#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Util/OpQueue.h>
#include <Util/Singleton.h>
#include <string>

namespace LOGL {
class Glfw : public KTKR::Singleton<Glfw>{
   public:
    //static Glfw* getInstance();
    void Init(size_t width = 800, size_t height = 600, const std::string & title = "Title");
    
    Glfw();
    ~Glfw();
    
    void Run(KTKR::OpQueue* opList);
    void Run(KTKR::Ptr<KTKR::OpQueue> &opList);
    void CloseWindow();
    void Terminate();
    GLFWwindow* getWindow();

    float deltaTime;

    const std::function<void()> _startOp;
    const std::function<void()> _endOp;
   private:

    float lastTime;
    // static Glfw* instance;
    GLFWwindow* window;
    static void updateViewport(GLFWwindow* window, int width, int height);
};
}  // namespace LOGL
