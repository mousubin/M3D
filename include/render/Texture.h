//
//  Texture.h
//  
//
//  Created by msb on 14-9-29.
//
//

#ifndef _Texture_h
#define _Texture_h

#include "RenderTypes.h"

namespace mrd {
    
    class Texture
    {
    };
    
    class Texture2D : public Texture
    {
        int _width, _height;
        int _format;
        int _nMipMaps;
        int _components;
        unsigned int _id;
    public:
        static Texture2D *create() {
            Texture2D *pTex = new Texture2D;
            return pTex;
        }
    public:
        Texture2D() {
            init();
        }
        operator unsigned int () { return _id; }
        void init() {
            _width = _height = 0;
            _format = 0;
            _nMipMaps = 0;
            _components = 0;
            glGenTextures(1, &_id);
        }
        void apply() {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _id);
        }
        //void setData(int level, int format, int width, int height, int type, void *data) {
        void setData(int width, int height, void *data) {
            _width = width;
            _height = height;
            _components = 4;
            _nMipMaps = 1;
            _format = GL_RGBA;
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);           
        }
        void compressImage(int width, int height, int format, int bufSize, void *buf) {
            _width = width;
            _height = height;
            _components = 4;
            _nMipMaps = 1;
            _format = GL_RGBA;
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _id);
            glCompressedTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, bufSize, buf);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
    };
    
    
    class TextureFactory
    {
    public:
        static Texture2D *loadTexture2D(const char *buf, int bufSize);
        static Texture2D *loadTexture2D_DDS(const char *buf, int bufSize);
    };
}


#endif
