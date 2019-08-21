#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <LOGL/Shader.h>
#include <iostream>

using namespace std;
using namespace LOGL;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(int argc, char const* argv[]) {
    /* init */
    glfwInit();
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* create window */
    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //////////START
    //顶点信息
    float vertices[] = {
        0.5f,  0.5f,  0.0f,  // 右上角
        0.5f,  -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f,  // 左下角
        -0.5f, 0.5f,  0.0f,  // 左上角
        0.0f,  0.0f,  0.0f   //中心
    };
    unsigned int indices[] = {
        // 注意索引从0开始!
        0, 3, 4,  // 第一个三角形
        4, 2, 1   // 第二个三角形
    };
    float tri1[] = {
        // 0.5f,  0.5f,  0.0f,  // 右上角
        // 0.5f,  -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f,  // 左下角
        -0.5f, 0.5f,  0.0f,  // 左上角
        0.0f,  0.0f,  0.0f   //中心
    };
    float tri2[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        // -0.5f, -0.5f, 0.0f,  // 左下角
        // -0.5f, 0.5f,  0.0f,   // 左上角
        0.0f, 0.0f, 0.0f  //中心
    };

    Shader shader("./src/01_Introduction/02_Triangle/vertex.vs",
                  "./src/01_Introduction/02_Triangle/frag_orange.fs");
    Shader shader1("./src/01_Introduction/02_Triangle/vertex.vs",
                   "./src/01_Introduction/02_Triangle/frag_yellow.fs");

    //////////链接顶点属性
    unsigned int VAO[2], VBO[2];
    //生成2个VAO对象
    glGenVertexArrays(2, VAO);
    //生成2个VBO对象
    glGenBuffers(2, VBO);
    // glGenBuffers(1, &VBO[0])

    //*** 1st VAO ***//
    glBindVertexArray(VAO[0]);

    //绑定缓冲对象(Array Buffer)
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    //把之前定义的顶点数据复制到缓冲的内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /*
    GL_STATIC_DRAW ：数据不会或几乎不会改变。
    GL_DYNAMIC_DRAW：数据会被改变很多。
    GL_STREAM_DRAW ：数据每次绘制时都会改变。
    */

    // EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    //绑定缓冲对象(Element Array Buffer)
    //,注意每种只能绑定一个，即此时无法再绑定GL_ARRAY_BUFFER类型的缓冲对象了
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    //*** 2nd VAO ***//
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri2), tri2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    //////////END

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        // render process
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        shader1.Use();
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // render end
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
