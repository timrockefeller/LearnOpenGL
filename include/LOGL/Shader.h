#pragma once
#include <string>
namespace LOGL {
class Shader {
   public:
    Shader(const std::string& vertexShaderPath,
           const std::string& fragmentShaderPath);
    ~Shader();
    void Use();
    void setBool(const std::string & name,bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);

   private:
    bool isValid();
    size_t shaderProgram;
};
}  // namespace LOGL
