//
//  GLTexture.hpp
//  Texture
//
//  Created by flybywind on 16/6/1.
//
//

#ifndef GLTexture_hpp
#define GLTexture_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
class GLTexture {
public:
    GLTexture();
    GLTexture(GLenum target);
    GLTexture(const char* texture_path);

    ~GLTexture();
    
    GLuint GetRef() {return _texture;};
    bool Valid() { return GetRef() > 0; };
    void SetParameteri(GLenum type, GLint value) {
        glTexParameteri(_target, type, value);
    }
    void SetImage(const char *filename,
                int channels,
                GLuint mmlayer,
                GLint innerformat) {
        _image = SOIL_load_image(filename,
                                 &_w, &_h, 0, channels);
        glTexImage2D(_target, mmlayer, innerformat, _w, _h,
                    0, innerformat, GL_UNSIGNED_BYTE, _image);
    }

    void Unbind(){
        if (!_texture) {
            glBindTexture(_target, 0);
            _texture = 0;
        }
    }
    
    bool Active() {
        if (_texture > 0) {
            glBindTexture(_target, _texture);
            return true;
        }else {
            return false;
        }
    }
        
    void SwitchUnit(GLint loc, GLuint uid);
    void GenMinMap() {
        glGenerateMipmap(_target);
    }
private:
    GLuint _texture;
    GLenum _target;
    unsigned char* _image;
    int _w;
    int _h;
};
#endif /* GLTexture_hpp */
