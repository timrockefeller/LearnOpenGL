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

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check valid
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::Use() {
    if (isValid())
        glUseProgram(shaderProgram);
}

bool Shader::isValid() {
    return glIsProgram(shaderProgram);
}

void Shader::setBool(const std::string& name, bool value) {
    Use();
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) {
    Use();
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) {
    Use();
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
