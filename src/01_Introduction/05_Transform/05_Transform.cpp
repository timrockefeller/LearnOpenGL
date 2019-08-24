#include <LOGL/Glfw.h>
#include <LOGL/Shader.h>
// #include <Util/Image.h>
#include <LOGL/Texture.h>
#include <Util/OpQueue.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace KTKR;
using namespace LOGL;
using namespace std;
int main(int argc, char const* argv[]) {
    const string title = "01_05: Trandformations";
    const uint32_t width = 800;
    const uint32_t height = 600;
    Glfw::getInstance()->Init(width, height, title);

    float vertices[] = {
        // ---- 位置 ----   ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f,  0.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f,  // 右上
        0.5f,  -0.5f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f, 0.0f,  // 右下
        -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  // 左下
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f   // 左上
    };
    unsigned int indices[] = {
        // 注意索引从0开始!
        0, 1, 3,  // 第一个三角形
        1, 2, 3   // 第二个三角形
    };

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // textures

    // unsigned int textures[2];
    // glGenTextures(2, textures);

    // glBindTexture(GL_TEXTURE_2D, textures[0]);
    // Image* texImage1 = new Image("assets/textures/container.jpg");
    // if (texImage1->isValid()) {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texImage1->getWidth(),
    //                  texImage1->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE,
    //                  texImage1->getData());
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // } else {
    //     cout << "Failed to load texture" << endl;
    // }

    // glBindTexture(GL_TEXTURE_2D, textures[1]);
    // Image* texImage2 = new Image("assets/textures/awesomeface.png");
    // if (texImage2->isValid()) {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImage2->getWidth(),
    //                  texImage2->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
    //                  texImage2->getData());
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // } else {
    //     cout << "Failed to load texture" << endl;
    // }
    Texture texture1("assets/textures/container.jpg"),
        texture2("assets/textures/awesomeface.png", true);
    // shaders
    Shader* shader =
        new Shader("src/01_Introduction/05_Transform/vertex.vs",
                   "src/01_Introduction/05_Transform/frag_texture.fs");
    shader->Use();
    shader->Use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);

    // transform
    // after version 0.9.9, mat4 initial to (zero)
    // glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0,
    // 0.0, 1.0)); trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    // shader->setMat4f("transform", trans);

    // loop
    OpQueue opList;
    opList << new Operation([&]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glActiveTexture(GL_TEXTURE0);  // 在绑定纹理之前先激活纹理单元
        // glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, textures[1]);

        texture1.setUnit(0);
        texture2.setUnit(1);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(),  // swap
                            glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        shader->setMat4f("transform", trans);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // second transformation
        // ---------------------
        trans = glm::mat4(1.0f);  // reset it to identity matrix
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = sin(glfwGetTime());
        trans =
            glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        shader->setMat4f("transform", trans);
        // now with the uniform matrix being replaced with new transformations,
        // draw it again.
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
/* Why does our container now spin around our screen?:
== ===================================================
Remember that matrix multiplication is applied in reverse. This time a
translation is thus applied first to the container positioning it in the
bottom-right corner of the screen. After the translation the rotation is applied
to the translated container.

A rotation transformation is also known as a change-of-basis transformation
for when we dig a bit deeper into linear algebra. Since we're changing the
basis of the container, the next resulting translations will translate the
container based on the new basis vectors. Once the vector is slightly rotated,
the vertical translations would also be slightly translated for example.

If we would first apply rotations then they'd resolve around the rotation origin
(0,0,0), but since the container is first translated, its rotation origin is no
longer (0,0,0) making it looks as if its circling around the origin of the
scene.

If you had trouble visualizing this or figuring it out, don't worry. If you
experiment with transformations you'll soon get the grasp of it; all it takes
is practice and experience.
*/
