#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Util/OpQueue.h>
#include <string>

namespace LOGL {
class Glfw {
   public:
    static Glfw* getInstance();
    void Init(size_t width = 800, size_t height = 600, const std::string & title = "Title");
    
    Glfw();
    static Glfw* instance;
    
    void Run(KTKR::OpQueue *opList);
    void CloseWindow();
    void Terminate();
GLFWwindow* window;
   private:
    
};
}  // namespace LOGL
