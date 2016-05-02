//
//  GLShader.cpp
//  HelloTriangle
//
//  Created by flybywind on 16/5/2.
//
//
#include "GLShader.hpp"

GLchar GLShader::Version[4] = "330";
GLShader::GLShader(const GLchar** vertex_shader, GLuint line,
                   const GLchar** fragment_shader, GLuint line2):
_success_code(0) {
    
    GLchar* _buffer;
    _buffer = _make_source(vertex_shader, line);
    printf("vertex source is: %s\n", _buffer);

    _vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    _compile(_buffer, _vertex_shader);
    delete []_buffer;
    if (!_success_code) {
        return;
    }

    _buffer = _make_source(fragment_shader, line2);
    printf("fragment source is: %s\n", _buffer);

    _fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    _compile(_buffer, _fragment_shader);
    delete []_buffer;
    if (!_success_code) {
        return;
    }
}
GLShader::GLShader(const GLchar* vertexPath,
                   const GLchar* fragmentPath) {
        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensures ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try
        {
            // Open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // Convert stream into GLchar array
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar* _buffer = vertexCode.c_str();
        printf("vertex source is: %s\n", _buffer);
        _vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        _compile(_buffer, _vertex_shader);

        if (!_success_code) {
            return;
        }
        
        _buffer = fragmentCode.c_str();
        printf("fragment source is: %s\n", _buffer);
        _fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        _compile(_buffer, _fragment_shader);
        if (!_success_code) {
            return;
        }
}
GLboolean GLShader::Link() {
    if (!_success_code) {
        return GL_FALSE;
    }
    _shader_prog = glCreateProgram();
    glAttachShader(_shader_prog, _vertex_shader);
    glAttachShader(_shader_prog, _fragment_shader);
    glLinkProgram(_shader_prog);
    glGetProgramiv(_shader_prog, GL_LINK_STATUS, &_success_code);
    
    if (!_success_code) {
        glGetProgramInfoLog(_shader_prog, SHADER_ERROR_LENGTH, NULL, _error_msg);
        return GL_FALSE;
    }
    return GL_TRUE;
}
void GLShader::UseProgram() {
    glUseProgram(_shader_prog);
}
void GLShader::Uniform4f(const GLchar* var_name,
                         GLfloat v0,
                         GLfloat v1,
                         GLfloat v2,
                         GLfloat v3) {
    GLint Location = glGetUniformLocation(_shader_prog, var_name);
    UseProgram();
    glUniform4f(Location, v0, v1, v2, v3);
}
void GLShader::Uniform1f(const GLchar* var_name, GLfloat v) {
    GLint Location = glGetUniformLocation(_shader_prog, var_name);
    UseProgram();
    glUniform1f(Location, v);
}
GLboolean GLShader::Error(const GLchar** error) {
    if (!_success_code) {
        *error = _error_msg;
        return GL_FALSE;
    }
    return GL_TRUE;
}

GLShader::~GLShader() {
    glDeleteShader(_vertex_shader);
    glDeleteShader(_fragment_shader);
}
void GLShader::_compile(const GLchar* src, GLuint& shader) {
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &_success_code);
    if (!_success_code) {
        glGetShaderInfoLog(shader, SHADER_ERROR_LENGTH, NULL, _error_msg);
        return ;
    }
    return;
}
GLchar* GLShader::_make_source(const GLchar** str, GLuint len) {
    GLchar* _buffer;
    char version[100];
    GLuint ver_len = sprintf(version, "#version %s core\n", GLShader::Version);
    GLuint src_len = ver_len;
    for (GLuint i = 0; i < len; ++i) {
        src_len += strlen(str[i]) + 1;
    }
    _buffer = new GLchar[src_len + 2];
    strncpy(_buffer, version, ver_len);
    GLuint p = ver_len;
    for (GLuint i = 0; i < len; ++i) {
        GLuint l = strlen(str[i]);
        strncpy(_buffer+p, str[i], l);
        p += l;
        _buffer[p++] = '\n';
    }
    _buffer[p] = '\0';
    
    return _buffer;
}