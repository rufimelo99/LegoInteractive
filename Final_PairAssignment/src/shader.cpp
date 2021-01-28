#include "shader.h"
#include <string>
#include <sstream>
#include <fstream>
#include "matrices.h"
#include <iostream>
using namespace std;


ShaderManager::ShaderManager() {}

ShaderManager::~ShaderManager() {
    glDeleteProgram(m_programID);
}


void ShaderManager::use() const {
    glUseProgram(getID());
}
void ShaderManager::unuse() const {
    glUseProgram(0);
}

void ShaderManager::addAtribute(const std::string& name, GLuint location) {
    glBindAttribLocation(m_programID, location, name.c_str());
}

void ShaderManager::setUniformV1(const std::string name, float v) {
    GLint location = getUniformLocation(name);
    glUniform1f(location, v);
}

void ShaderManager::setUniformV3(const std::string name, const Vectors::vector3D& v) {
    GLint location = getUniformLocation(name);
    glUniform3f(location, v.x, v.y, v.z);
}

void ShaderManager::setUniformV4(const std::string name, const Vectors::vector4D& v) {
    GLint location = getUniformLocation(name);
    glUniform4f(location, v.x, v.y, v.z, v.w);
}

void ShaderManager::setUniformMatrix4fv(const std::string name, const Matrices::matrix4D& m) {
    Matrices::matrix4D temp(m);
    GLint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, toOpenGL(temp));
}

GLint ShaderManager::getUniformLocation(const std::string name) {
    if (m_uniformCache.find(name) != m_uniformCache.end()) {
        return m_uniformCache[name];
    }
    GLint location = glGetUniformLocation(m_programID, name.c_str());
    if (location == -1) {
        std::cout << "Uniform " << name << " could not be found!" << std::endl;
    }
    m_uniformCache[name] = location;
    return location;
}

void ShaderManager::compileShaders(const std::string& vertexPath, const std::string& fragmentPath) {
    m_programID = glCreateProgram();
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexSource = parseShader(vertexPath);
    const GLchar* vertexShader = vertexSource.c_str();
    glShaderSource(m_vertexShaderID, 1, &vertexShader, 0);
    compileShader(m_vertexShaderID);

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentSource = parseShader(fragmentPath);
    const GLchar* fragmentShader = fragmentSource.c_str();
    glShaderSource(m_fragmentShaderID, 1, &fragmentShader, 0);
    compileShader(m_fragmentShaderID);

    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);

}

void ShaderManager::compileShader(GLuint shaderID) {
    glCompileShader(shaderID);
    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        char infoLog[512];
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(shaderID);
        std::cout << "ERROR: Shader compilation failed:\n" << infoLog << std::endl;
    }
    else
        std::cout << "Success: Shader compilation" << std::endl;

}


std::string ShaderManager::parseShader(const std::string& shaderPath) {
    std::stringstream shaderCode;
    std::ifstream file(shaderPath);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line))
        {
            shaderCode << line << '\n';
        }
        file.close();
    }
    else
        std::cout << "Unable to open file: " << shaderPath << std::endl;

    return shaderCode.str();
}

void ShaderManager::linkShaders() {

    glLinkProgram(m_programID);

    glDetachShader(m_programID, m_vertexShaderID);
    glDeleteShader(m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_fragmentShaderID);
}