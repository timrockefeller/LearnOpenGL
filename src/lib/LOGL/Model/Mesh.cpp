#include <LOGL/Mesh.h>
#include <LOGL/VAO.h>
using namespace LOGL;
// using namespace KTKR;
using namespace std;

Mesh::Mesh(std::vector<Vertex>& vertices,
           std::vector<unsigned int>& indices,
           std::vector<Texture>& textures)
    : vertices(vertices), indices(indices), textures(textures) {
    setupMesh();
}

void Mesh::Draw(Shader shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        // 获取纹理序号（diffuse_textureN 中的 N）
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);
        // custom by user
        shader.setInt((name + number).c_str(), i);
        textures[i].setUnit(i);
    }

    // 绘制网格
    // vao.Draw();
    glBindVertexArray(meshVAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh ::setupMesh() {
    // vao = VAO(&vertices[0], vertices.size() * sizeof(Vertex),
    //           {3, 3, 2}, &indices[0], indices.size() * sizeof(size_t));
    glGenVertexArrays(1, &meshVAO);
    glGenBuffers(1, &meshVBO);
    glGenBuffers(1, &meshEBO);

    glBindVertexArray(meshVAO);
    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshEBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);
    // sort data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &meshEBO);
    glDeleteBuffers(1, &meshEBO);
    glDeleteVertexArrays(1, &meshVAO);
}
