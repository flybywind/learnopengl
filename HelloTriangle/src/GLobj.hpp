//
//  GLobj.hpp
//  HelloTriangle
//
//  Created by flybywind on 16/5/2.
//
//

#ifndef GLobj_hpp
#define GLobj_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <vector>

#define STATIC_ARRAY_SIZE(ary) \
    sizeof(ary)/sizeof(ary[0])

class GLobj {
public:
    GLobj();
    ~GLobj();
    
    void SetVBO(const void*, GLuint);
    void SetEBO(const GLuint*, GLuint);
    
    void Bind();
    void Draw(GLenum shape);
    void Draw(GLenum shape, GLuint count);
    void Draw(GLenum, GLuint start, GLuint count);
    // 设置 vertex attribute 的位置。在vertex shader里面，通过指定layout (location = index)
    // 设置位置，此处需要和那里对应。
    void SetVertexAttribIndex(GLuint);
    void SetVertexAttribSize(GLint);
    void SetVertexAttribType(GLenum);
    void SetVertexAttribNorm(GLboolean);
    void SetVertexAttribStrid(GLsizei);
    void SetVertexAttribOffset(GLvoid*);
    void SetDrawUsage(GLenum);
    

private:
    const void * _vbo_ary;
    GLuint _vbo_ary_len;
    GLuint _vbo_ary_byte_len;
    const GLuint * _ebo_ary;
    GLuint _ebo_ary_len;
    // 需要注意多线程加锁：
    static GLuint _id;
    static GLuint _increase_id();
    
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    GLuint _vertex_attr_index;
    GLint _vertex_attr_size;
    GLenum _vertex_attr_type;
    GLboolean _vertex_attr_normalized;
    GLsizei _vertex_attr_stride;
    GLvoid* _vertex_attr_offset;
    
    GLboolean _use_ebo;
    GLenum _draw_usage;
    GLboolean _has_binded;
};

#endif /* GLobj_hpp */
