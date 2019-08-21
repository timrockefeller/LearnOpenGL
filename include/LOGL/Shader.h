#pragma once
#include<string>
namespace LOGL {
class Shader {
    public:
    Shader(const std::string& vertexShaderPath,
           const std::string& fragmentShaderPath);
    ~Shader();
    void Use();

   private:
    size_t shaderProgram;
};
}  // namespace LOGL
