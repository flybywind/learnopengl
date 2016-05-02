//
//  GLShader.hpp
//  HelloTriangle
//
//  Created by flybywind on 16/5/2.
//
//

#ifndef GLShader_hpp
#define GLShader_hpp

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define SHADER_ERROR_LENGTH 512

class GLShader {
public:
    static GLchar Version[4];
    GLShader(const GLchar** vertex_shader, GLuint line,
             const GLchar** fragment_shader, GLuint line2);

    GLShader(const GLchar* vertexPath,
             const GLchar* fragmentPath);
    ~GLShader();
    
    GLuint GetProgram() { return _shader_prog; }
    GLboolean Error(const GLchar** err_msg);
    GLboolean Link();
    void UseProgram();
    
    void Uniform1f(const GLchar* var_name, GLfloat v);
    void Uniform4f(const GLchar* var_name,
                   GLfloat v0,
                   GLfloat v1,
                   GLfloat v2,
                   GLfloat v3);

private:
    GLchar* _make_source(const GLchar**, GLuint);
    void _compile(const GLchar*, GLuint& shader);
    GLchar _error_msg[SHADER_ERROR_LENGTH];
    GLint _success_code;
    GLuint _vertex_shader;
    GLuint _fragment_shader;
    GLuint _shader_prog;
    
    GLShader() {};
    
};
#endif /* GLShader_hpp */
