#pragma once
#include <LOGL/Shader.h>
#include <LOGL/Texture.h>
#include <LOGL/VAO.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>
namespace LOGL {
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
   public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Mesh(std::vector<Vertex> vertices,
         std::vector<unsigned int> indices,
         std::vector<Texture> textures);
    void Draw(Shader shader);
   private:
    VAO vao;
    void setupMesh();
};

}  // namespace LOGL
