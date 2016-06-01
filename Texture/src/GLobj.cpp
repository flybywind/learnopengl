//
//  GLobj.cpp
//  HelloTriangle
//
//  Created by flybywind on 16/5/2.
//
//

#include "GLobj.hpp"


GLobj::GLobj():
_vbo_ary_len(0),
_ebo_ary_len(0),
_vertex_attr_index(0),
_vertex_attr_size(4),
_vertex_attr_type(GL_FLOAT),
_vertex_attr_normalized(GL_FALSE),
_vertex_attr_stride(0),
_vertex_attr_offset((GLvoid*)0),
_use_ebo(GL_FALSE),
_draw_usage(GL_DYNAMIC_DRAW),
_has_binded(GL_FALSE),
_shader(NULL) {
    _vbo_ary_byte_len = sizeof(GLfloat);
    glGenVertexArrays(1, &_vao);
    printf("gen VAO: %d\n", _vao);
}

GLobj::~GLobj() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    
    printf("del VAO: %d\n", _vao);
    printf("del VBO: %d\n", _vbo);
    
    if (_use_ebo) {
        glDeleteBuffers(1, &_ebo);
        printf("del EBO: %d\n", _ebo);
    }
}

void GLobj::SetVBO(const void* a, GLuint len) {
    // TODO: 防止内存泄露，如果vbo已经绑定了数据，就应该重新初始化状态
    _vbo_ary = a;
    _vbo_ary_len = len;
    glGenBuffers(1, &_vbo);
    printf("gen VBO: %d\n", _vbo);

}

void GLobj::SetEBO(const GLuint* a, GLuint len) {
    _ebo_ary = a;
    _ebo_ary_len = len;
    _use_ebo = GL_TRUE;
    glGenBuffers(1, &_ebo);
    printf("gen EBO: %d\n", _ebo);
}
void GLobj::SetShader(GLShader* shader) {
    _shader = shader;
}
void GLobj::StartBind() {
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
    
}
void GLobj::EnableAttrib() {
    glVertexAttribPointer(_vertex_attr_index,
                          _vertex_attr_size,
                          _vertex_attr_type,
                          _vertex_attr_normalized,
                          _vertex_attr_stride,
                          _vertex_attr_offset);
    
    glEnableVertexAttribArray(_vertex_attr_index);
}
void GLobj::EndBind() {
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
    if  (_shader != NULL) {
        _shader->UseProgram();
    } else {
        fprintf(stderr, "no shader attached!\n");
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
    _vertex_attr_stride = strid * _vbo_ary_byte_len;
}
void GLobj::SetVertexAttribOffset(GLuint p) {
    _vertex_attr_offset = (GLvoid*)(p * _vbo_ary_byte_len);
}
void GLobj::SetDrawUsage(GLenum draw_usage) {
    _draw_usage = draw_usage;
}