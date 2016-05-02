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
    _buffer =  _make_source(vertex_shader, line);
    printf("vertex source is: %s\n", _buffer);

    _vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertex_shader, 1, &_buffer, NULL);
    glCompileShader(_vertex_shader);
    glGetShaderiv(_vertex_shader, GL_COMPILE_STATUS, &_success_code);
    if (!_success_code) {
        glGetShaderInfoLog(_vertex_shader, SHADER_ERROR_LENGTH, NULL, _error_msg);
        return;
    }
    delete []_buffer;

    _buffer = _make_source(fragment_shader, line2);
    printf("fragment source is: %s\n", _buffer);

    _fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragment_shader, 1, &_buffer, NULL);
    glCompileShader(_fragment_shader);
    glGetShaderiv(_fragment_shader, GL_COMPILE_STATUS, &_success_code);
    if (!_success_code) {
        glGetShaderInfoLog(_fragment_shader, SHADER_ERROR_LENGTH, NULL, _error_msg);
    }
    delete []_buffer;
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