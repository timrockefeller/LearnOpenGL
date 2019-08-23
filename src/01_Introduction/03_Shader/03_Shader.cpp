#include <cmath>
#include <LOGL/Glfw.h>
#include <LOGL/Shader.h>
#include <Util/OpQueue.h>
using namespace std;
using namespace KTKR;
using namespace LOGL;

int main(int argc, char const* argv[]) {
    const string title = "1-3 Shader";
    const int width = 800;
    const int height = 600;
    Glfw::getInstance()->Init(width, height, title);


    float vertices[] = {
        // 位置              // 颜色
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // 左下
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // 顶部
    };

    unsigned int VAO,VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    //glad_glVertexAttribPointer(index, size, type, normalized, stride, *pointer);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader* shader1 = new Shader("./src/01_Introduction/03_Shader/vertex.vs",
                                 "./src/01_Introduction/03_Shader/frag_color.fs");

    
    OpQueue opList;
    opList << new Operation([&]() {  // clearing
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //}) << new Operation([]() {  // end
        shader1->Use();
        float sins = sin(glfwGetTime());
        shader1->setFloat("lighting", (sins / 4.0f) + 0.75f);
        shader1->setFloat("offset", sins / 4.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(Glfw::getInstance()->getWindow());
        glfwPollEvents();
    });
    Glfw::getInstance()->Run(&opList);
    return 0;
}
/* 
Answer to the question: Do you know why the bottom-left side is black?
-- --------------------------------------------------------------------
Think about this for a second: the output of our fragment's color is equal to the (interpolated) coordinate of 
the triangle. What is the coordinate of the bottom-left point of our triangle? This is (-0.5f, -0.5f, 0.0f). Since the
xy values are negative they are clamped to a value of 0.0f. This happens all the way to the center sides of the 
triangle since from that point on the values will be interpolated positively again. Values of 0.0f are of course black
and that explains the black side of the triangle.
*/
