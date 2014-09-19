//
//  Vertex.h
//  
//
//  Created by msb on 14-9-19.
//
//

#ifndef _Vertex_h
#define _Vertex_h

#include "RenderTypes.h"

namespace mrd {
    
    
    class VertexBuffer
    {
        unsigned int _idBuf;
        unsigned int _vertexArray;
        int _attribs[16];
        int _nAttribs;
        int _stride;
    public:
        VertexBuffer() { _nAttribs = 0; _idBuf = 0; _stride = 0; }
        void setData(void *buf, int sz, unsigned int attrib) {
            //glGenVertexArraysOES(1, &_vertexArray);
            //glBindVertexArrayOES(_vertexArray);
            
            glGenBuffers(1, &_idBuf);
            glBindBuffer(GL_ARRAY_BUFFER, _idBuf);
            glBufferData(GL_ARRAY_BUFFER, sz, buf, GL_STATIC_DRAW);
            
            _nAttribs = 0;
            int type = 0;
            while (attrib) {
                if (attrib & 0x1) {
                    _attribs[_nAttribs++] = type;
                }
                type++;
                attrib >>= 1;
            }
            
            for (int i=0; i<_nAttribs; i++) {
                _stride += __vaConfig[_attribs[i]].width;
            }
        }
        void setPointer() {
            int offset = 0;
            for (int i=0; i<_nAttribs; i++) {
                int j = _attribs[i];
                glVertexAttribPointer(i, __vaConfig[j].size, __vaConfig[j].type,
                                      __vaConfig[j].normalized, _stride, (void *)(long)offset);
                offset += __vaConfig[j].width;
            }
        }
        void bindAttrib(unsigned int iPG) {
            for (int i=0; i<_nAttribs; i++){
                glBindAttribLocation(iPG, i, __vaConfig[_attribs[i]].name);
            }
        }
        void apply() {
            glBindBuffer(GL_ARRAY_BUFFER, _idBuf);
            setPointer();
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
        }
    };
    
    class VertexObject
    {
    
    };
    
};

#endif