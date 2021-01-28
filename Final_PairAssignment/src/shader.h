#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <string>
#include "vector4d.h"
#include "matrix4d.h"
#include <unordered_map>

class ShaderManager {
private:
    GLuint m_programID;
    GLuint m_vertexShaderID, m_fragmentShaderID;
    std::unordered_map<std::string, int> m_uniformCache;

public:
    ShaderManager();
    ~ShaderManager();

    GLuint getID() const {
        return m_programID;
    }
    void use() const;
    void unuse() const;

    void addAtribute(const std::string& name, GLuint location);
    void setUniformV1(const std::string name, float v);
    void setUniformV3(const std::string name, const Vectors::vector3D& v);
    void setUniformV4(const std::string name, const Vectors::vector4D& v);
    void setUniformMatrix4fv(const std::string name, const Matrices::matrix4D& m);
    void compileShaders(const std::string& vertexPath, const std::string& fragmentPath);
    void linkShaders();
private:
    GLint getUniformLocation(const std::string name);
    void compileShader(GLuint shaderID);
    std::string parseShader(const std::string& shaderPath);
};

#endif