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

#define SHADER_ERROR_LENGTH 512

class GLShader {
public:
    static GLchar Version[4];
    GLShader(const GLchar** vertex_shader, GLuint line,
             const GLchar** fragment_shader, GLuint line2);
    ~GLShader();
    
    GLboolean Error(const GLchar** err_msg);
    GLboolean Link();
    void UseProgram();
private:
    GLchar* _make_source(const GLchar**, GLuint);
    
    GLchar _error_msg[SHADER_ERROR_LENGTH];
    GLint _success_code;
    GLuint _vertex_shader;
    GLuint _fragment_shader;
    GLuint _shader_prog;
    
    GLShader() {};
    
};
#endif /* GLShader_hpp */
