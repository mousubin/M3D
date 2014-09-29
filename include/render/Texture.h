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
    
    
    class Texture2D
    {
        int _width, _height;
        int _format;
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
            glGenTextures(1, &_id);
        }
        void apply() {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _id);
        }
        //void setData(int level, int format, int width, int height, int type, void *data) {
        void setData(int width, int height, void *data) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _id);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);           
        }
    };
}


#endif
