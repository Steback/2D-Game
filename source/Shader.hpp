#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include "glad/glad.h"

class Shader {
    public:
        Shader(const std::string &vertexFilePath_, const std::string &fragmentFilePath_);
        ~Shader();
        GLuint getUniformLocation(const std::string& name_) const;
        void useShader() const;
        void clearShader() const;

    private:
        GLuint shaderID;

        void compileShader(const std::string& vertexCode_, const std::string& fragmentCode_);
        static void addShader(GLuint program_, const std::string& shaderCode_, GLenum shaderType_) ;
        static std::string readFile(const std::string& filePath_);
};

#endif
