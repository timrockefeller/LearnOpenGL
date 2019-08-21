#pragma once
#include<string>
namespace LOGL {
class Shader {
    Shader(const std::string& vertexShaderPath,
           const std::string& fragmentShaderPath);
    ~Shader();
};
}  // namespace LOGL
