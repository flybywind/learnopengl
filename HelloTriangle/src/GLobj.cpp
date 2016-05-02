//
//  GLobj.cpp
//  HelloTriangle
//
//  Created by flybywind on 16/5/2.
//
//

#include "GLobj.hpp"

GLuint GLobj::_id = 0;
GLuint GLobj::_increase_id() {
    // 多线程不安全
    return ++_id;
}

GLobj::GLobj():
_vertex_attr_index(0),
_vertex_attr_size(4),
_vertex_attr_type(GL_FLOAT),
_vertex_attr_normalized(GL_FALSE),
_vertex_attr_stride(0),
_vertex_attr_offset((GLvoid*)0),
_use_ebo(GL_FALSE),
_draw_usage(GL_DYNAMIC_DRAW),
_has_binded(GL_FALSE) {
    _vao = GLobj::_increase_id();
    _vbo = _vao;
    _vbo_ary_byte_len = sizeof(GLfloat);
    glGenBuffers(1, &_vao);
}

GLobj::~GLobj() {
    printf("dealloc GLobj");
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    if (_use_ebo) {
        glDeleteBuffers(1, &_ebo);
    }
}

void GLobj::SetVBO(const void* a, GLuint len) {
    _vbo_ary = a;
    _vbo_ary_len = len;
    glGenVertexArrays(1, &_vbo);
}

void GLobj::SetEBO(const GLuint* a, GLuint len) {
    _ebo_ary = a;
    _ebo_ary_len = len;
    _use_ebo = GL_TRUE;
    _ebo = _vbo;
    glGenBuffers(1, &_ebo);
}

void GLobj::Bind() {
    if (_has_binded) {
        return;
    }
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 _vbo_ary_byte_len * _vbo_ary_len,
                 _vbo_ary, _draw_usage);
    if (_use_ebo) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(GLuint) * _ebo_ary_len,
                     _ebo_ary, _draw_usage);
    }
    
    glVertexAttribPointer(_vertex_attr_index,
                          _vertex_attr_size,
                          _vertex_attr_type,
                          _vertex_attr_normalized,
                          _vertex_attr_stride,
                          _vertex_attr_offset);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    _has_binded = GL_TRUE;
}

void GLobj::Draw(GLenum shape) {
    GLuint count;
    if (_use_ebo) {
        count = _ebo_ary_len;
    } else {
        count = _vbo_ary_len;
    }
    Draw(shape, 0, count);
}

void GLobj::Draw(GLenum shape, GLuint count) {
    Draw(shape, 0, count);
}

void GLobj::Draw(GLenum shape, GLuint start, GLuint count) {
    if (!_has_binded) {
        fprintf(stderr, "GLobj::Draw[fatal]: bind hasn't been executed!\n");
        return;
    }
    glBindVertexArray(_vao);

    if (_use_ebo) {
        glDrawElements(shape, (GLsizei)count, GL_UNSIGNED_INT, (GLvoid*)(_ebo+start));
    } else {
        glDrawArrays(shape, start, count);
    }
    
    glBindVertexArray(0);

}
void GLobj::SetVertexAttribIndex(GLuint ind){
    _vertex_attr_index = ind;
}
void GLobj::SetVertexAttribSize(GLint size) {
    _vertex_attr_size = size;
}
void GLobj::SetVertexAttribType(GLenum type) {
    _vertex_attr_type = type;
    switch (type) {
        case GL_FLOAT:
            _vbo_ary_byte_len = sizeof(GLfloat);
            break;
        case GL_DOUBLE:
            _vbo_ary_byte_len = sizeof(GLdouble);
        case GL_INT:
            _vbo_ary_byte_len = sizeof(GLint);
            break;
        case GL_UNSIGNED_INT:
            _vbo_ary_byte_len = sizeof(GLuint);
            break;
        case GL_UNSIGNED_SHORT:
            _vbo_ary_byte_len = sizeof(GLushort);
            break;
        case GL_SHORT:
            _vbo_ary_byte_len = sizeof(GLshort);
            break;
        case GL_BYTE:
            _vbo_ary_byte_len = sizeof(GLbyte);
            break;
        case GL_UNSIGNED_BYTE:
            _vbo_ary_byte_len = sizeof(GLubyte);
            break;
        default:
            fprintf(stderr, "GLobj::SetVertexAttribType[fatal]: unsupported type!");
            _vbo_ary_byte_len = 0;
            break;
    }
}
void GLobj::SetVertexAttribNorm(GLboolean norm_flag) {
    _vertex_attr_normalized = norm_flag;
}
void GLobj::SetVertexAttribStrid(GLsizei strid) {
    _vertex_attr_stride = strid;
}
void GLobj::SetVertexAttribOffset(GLvoid* p) {
    _vertex_attr_offset = p;
}
void GLobj::SetDrawUsage(GLenum draw_usage) {
    _draw_usage = draw_usage;
}