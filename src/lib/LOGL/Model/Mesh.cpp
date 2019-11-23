#include <LOGL/Mesh.h>
#include <LOGL/VAO.h>
using namespace LOGL;
// using namespace KTKR;
using namespace std;

Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<unsigned int> indices,
           std::vector<Texture> textures)
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
            number = std::to_string(
                specularNr++);
        else if (name == "texture_normal")
            number =
                std::to_string(normalNr++);
        else if (name == "texture_height")
            number =
                std::to_string(heightNr++);
        // custom by user
        shader.setInt((name + number).c_str(), i);
        textures[i].setUnit(i);
    }

    // 绘制网格
    vao.Draw();
}

void Mesh ::setupMesh() {
    vao = VAO((float *)&vertices, vertices.size() * sizeof(Vertex),
              {3, 3, 2}, &(indices[0]), indices.size());
}
