//
//  GLTexture.cpp
//  Texture
//
//  Created by flybywind on 16/6/1.
//
//

#include "GLTexture.hpp"

GLTexture::GLTexture():
_texture(0),
_target(GL_TEXTURE_2D),
_image(nullptr) {
    glGenTextures(1, &_texture);
    glBindTexture(_target, _texture);
}

GLTexture::GLTexture(GLenum target):
_texture(0),
_image(nullptr) {
    _target = target;
    glGenTextures(1, &_texture);
    glBindTexture(_target, _texture);
}

GLTexture::GLTexture(const char* texture_path):
_target(GL_TEXTURE_2D) {
    glGenTextures(1, &_texture);
    glBindTexture(_target, _texture);
    SetImage(texture_path, SOIL_LOAD_RGB, 0, GL_RGB);
}
GLTexture::~GLTexture() {
    if (nullptr != _image) {
        SOIL_free_image_data(_image);
    }
    Unbind();
}

void GLTexture::SwitchUnit(GLint loc, GLuint uid) {
    glActiveTexture(GL_TEXTURE0+uid);
    if (Active()) {
        glUniform1i(loc, uid);
    }
}