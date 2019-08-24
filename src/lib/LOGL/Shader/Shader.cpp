#include <glad/glad.h>

#include <iostream>

#include <LOGL/Shader.h>
#include <Util/File.h>
using namespace std;
using namespace LOGL;
using namespace KTKR;
Shader::Shader(const string& vertexShaderPath,
               const string& fragmentShaderPath) {
    File vsF(vertexShaderPath, File::Mode::READ);
    string vss = vsF.ReadAll();
    const char* vertexShaderSource = vss.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    // check valid
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
             << infoLog << endl;
    }

    File fsF(fragmentShaderPath, File::Mode::READ);
    string fss = fsF.ReadAll();
    const char* fragmentShaderSource = fss.c_str();

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    // check valid
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::Use() const {
    if (isValid())
        glUseProgram(ID);
}

bool Shader::isValid() const {
    return glIsProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    Use();
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const {
    Use();
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
    Use();
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::SetMat4f(const std::string& name, const float* matValue) const {
    Use();
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1,
                       GL_FALSE, matValue);
}
void Shader::setMat4f(const std::string& name, glm::mat4 mat4) const {
    SetMat4f(name, glm::value_ptr(mat4));
}
