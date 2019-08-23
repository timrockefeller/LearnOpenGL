#include <LOGL/Glfw.h>
#include <LOGL/Shader.h>
#include <Util/Image.h>
#include <Util/OpQueue.h>
#include <iostream>
using namespace KTKR;
using namespace LOGL;
using namespace std;
int main(int argc, char const* argv[]) {
    const string title = "01_04: Textures";
    const uint32_t width = 800;
    const uint32_t height = 600;
    Glfw::getInstance()->Init(width, height, title);

    float texCoords[] = {
        0.0f, 0.0f,  // 左下角
        1.0f, 0.0f,  // 右下角
        0.5f, 1.0f   // 上中
    };
    float vertices[] = {
        // ---- 位置 ----   ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f,  // 右上
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,  // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 左下
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f   // 左上
    };

    unsigned int indices[] = {
        // 注意索引从0开始!
        0, 1, 3,  // 第一个三角形
        1, 2, 3   // 第二个三角形
    };

    ///////////Objects
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    /////////TEXTURE

    unsigned int texture1, texture2;

    glGenTextures(1, &texture1);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture1);
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Image* texImage1 = new Image("assets/textures/container.jpg");
    if (texImage1->isValid()) {
        glTexImage2D(GL_TEXTURE_2D,  //纹理目标
                     0,              //多级渐远纹理的级别
                     GL_RGB,         //储存方式
                     texImage1->getWidth(), texImage1->getHeight(), 0,  //参数
                     GL_RGB, GL_UNSIGNED_BYTE,  //原图片格式
                     texImage1->getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        cout << "Failed to load texture" << endl;
    }

    glBindTexture(GL_TEXTURE_2D, texture2);
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    Image* texImage2 = new Image("assets/textures/awesomeface.png");
    if (texImage2->isValid()) {
        glTexImage2D(GL_TEXTURE_2D,  //纹理目标
                     0,              //多级渐远纹理的级别
                     GL_RGBA,        //储存方式
                     texImage2->getWidth(), texImage2->getHeight(), 0,  //参数
                     GL_RGBA, GL_UNSIGNED_BYTE,  //原图片格式
                     texImage2->getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        cout << "Failed to load texture" << endl;
    }
    // free

    ////////Shader
    Shader* shader =
        new Shader("src/01_Introduction/04_Textures/vertex.vs",
                   "src/01_Introduction/04_Textures/frag_texture.fs");
    shader->Use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);

    OpQueue opList;
    opList << new Operation([&]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);  // 在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
        shader->Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(Glfw::getInstance()->getWindow());
        glfwPollEvents();
    });
    Glfw::getInstance()->Run(&opList);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    return 0;
}
