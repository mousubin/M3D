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
    
    struct ColorVertex
    {
        float x, y, z;
        unsigned int cr;
    };
    
    struct MeshVertex
    {
        float x, y, z;
        float xn, yn, zn;
    };
    
    struct ColorMeshVertex
    {
        float x, y, z;
        float xn, yn, zn;
        unsigned int cr;
    };
    
    struct ModelVertex
    {
        float x, y, z;
        float xn, yn, zn;
        float u, v;
    };
    
    struct ColorModelVertex
    {
        float x, y, z;
        float xn, yn, zn;
        float u, v;
        float cr;
    };
    
    struct UIImageVertex
    {
        float x, y, z;
        float u, v;
    };
    
    class VertexBuffer
    {
    public:
        unsigned int _idBuf;
        unsigned int _vertexArray;
        int _vertexCount;
        int _attribs[16];
        int _offset[16];
        int _nAttribs;
        int _stride;
        unsigned int _attribBits;
        int _nCurVertexArrays;
    public:
        VertexBuffer() { _nAttribs = 0; _idBuf = 0; _stride = 0; _attribBits = 0; _vertexCount = 0; }
        ~VertexBuffer() {
            if (_idBuf)
                glDeleteBuffers(1, &_idBuf);
        }
        void setData(void *buf, int sz, unsigned int attribBits) {
            _attribBits = attribBits;
            
            glGenBuffers(1, &_idBuf);
            glBindBuffer(GL_ARRAY_BUFFER, _idBuf);
            glBufferData(GL_ARRAY_BUFFER, sz, buf, GL_STATIC_DRAW);
            
            _nAttribs = 0;
            int type = 0;
            while (attribBits) {
                if (attribBits & 0x1) {
                    _attribs[_nAttribs++] = type;
                }
                type++;
                attribBits >>= 1;
            }
            
            for (int i=0; i<_nAttribs; i++) {
                _offset[i] = _stride;
                _stride += __vaConfig[_attribs[i]].width;
            }
            
            _vertexCount = sz / _stride;
        }
        int getVertexCount() { return _vertexCount; }
//        void setPointer() {
//            int offset = 0;
//            for (int i=0; i<_nAttribs; i++) {
//                int j = _attribs[i];
//                glVertexAttribPointer(i, __vaConfig[j].size, __vaConfig[j].type,
//                                      __vaConfig[j].normalized, _stride, (void *)(long)offset);
//                offset += __vaConfig[j].width;
//            }
//        }
        void bindAttrib(unsigned int iPG) {
            for (int i=0; i<_nAttribs; i++){
                glBindAttribLocation(iPG, i, __vaConfig[_attribs[i]].name);
            }
        }
//        // 如何开启关闭顶点属性数组
//        void apply() {
//            glBindBuffer(GL_ARRAY_BUFFER, _idBuf);
//            setPointer();
//            glEnableVertexAttribArray(0);
//            glEnableVertexAttribArray(1);
//        }
        void apply(unsigned int attribBits) {
            glBindBuffer(GL_ARRAY_BUFFER, _idBuf);
            int i = 0;
            int j = 0;
            unsigned int a0 = _attribBits;
            while (a0) {
                if (a0 & 0x1) {
                    if (attribBits & 0x1) {
                        int k = _attribs[i];
                        glVertexAttribPointer(j, __vaConfig[k].size, __vaConfig[k].type,
                            __vaConfig[k].normalized, _stride, (void *)(long)_offset[i]);
                        glEnableVertexAttribArray(j);
                        j++;
                    }
                    i++;
                }
                a0 >>= 1;
                attribBits >>= 1;
            }
            _nCurVertexArrays = j;
        }
    };
};

#endif
