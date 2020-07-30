#include <fstream>

#include "fmt/core.h"

#include "Shader.hpp"

Shader::Shader(const std::string &vertexFilePath_, const std::string &fragmentFilePath_) : shaderID(0) {
    compileShader(readFile(vertexFilePath_), readFile(fragmentFilePath_));
}

Shader::~Shader() {
    clearShader();
}

GLuint Shader::getUniformLocation(const std::string &name_) const {
    return glGetUniformLocation(shaderID, name_.c_str());
}

void Shader::useShader() const {
    glUseProgram(shaderID);
}

void Shader::clearShader() const {
    if ( shaderID != 0 ) glDeleteProgram(shaderID);
}

void Shader::compileShader(const std::string &vertexCode_, const std::string &fragmentCode_) {
    shaderID = glCreateProgram();

    if ( !shaderID ) {
        fmt::print("Error creating shader program\n");
        return ;
    }

    addShader(shaderID, vertexCode_, GL_VERTEX_SHADER);
    addShader(shaderID, fragmentCode_, GL_FRAGMENT_SHADER);

    glLinkProgram(shaderID);

    GLint result;
    GLchar eLog[1024];

    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

    if ( !result ) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        fmt::print("Error linking program: {}\n", eLog);
        return ;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

    if ( !result ) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        fmt::print("Error validating program: {}\n", eLog);
        return ;
    }
}

void Shader::addShader(GLuint program_, const std::string &shaderCode_, GLenum shaderType_) {
    GLuint shader = glCreateShader(shaderType_);

    const GLchar* shaderCode = shaderCode_.c_str();
    GLint codeLength = shaderCode_.length();

    glShaderSource(shader, 1, &shaderCode, &codeLength);
    glCompileShader(shader);

    GLint result;
    GLchar eLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if ( !result ) {
        glGetShaderInfoLog(shader, sizeof(eLog), nullptr, eLog);
        fmt::print("Error compiling {}  shader: {}\n", shader, eLog);
        return ;
    }

    glAttachShader(program_, shader);
}

std::string Shader::readFile(const std::string &filePath_) {
    std::string content;
    std::fstream fileStream(filePath_, std::ios::in);

    if ( !fileStream.is_open() ) {
        fmt::print("Fail to read {} file\n", filePath_);
        return "";
    }

    std::string line;

    while ( !fileStream.eof() ) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();

    return content;
}
