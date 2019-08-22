#include <LOGL/Glfw.h>
#include <Util/OpQueue.h>
using namespace std;
using namespace KTKR;
using namespace LOGL;

int main(int argc, char const* argv[]) {
    const string title = "1-3 Shader";
    const int width = 800;
    const int height = 600;

    Glfw::getInstance()->Init(width, height, title);
    OpQueue opList;
    opList << new Operation([]() {
        
        // render process
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // render end
        glfwSwapBuffers(Glfw::getInstance()->window);
        glfwPollEvents();
    },true);
    Glfw::getInstance()->Run(&opList);
    return 0;
}
