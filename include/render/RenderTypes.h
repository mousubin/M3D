//
//  RenderTypes.h
//  
//
//  Created by msb on 14-9-17.
//
//

#ifndef _RenderTypes_h
#define _RenderTypes_h

#ifdef __MRENDER_IOS__
#include <OpenGLES/ES2/gl.h>
#else
#include <OpenGL/gl.h>
#endif

enum ClearBufferBit{
    ColorBufferBit = GL_COLOR_BUFFER_BIT,
    DepthBufferBit = GL_DEPTH_BUFFER_BIT,
};

enum VertexAttribBit{
    VA_VEC = 1,
    VA_NORMAL = 2,
    VA_COLOR = 4,
    VA_TEX0 = 8
};

struct VertexAttrib
{
    int attrib;
    int size;
    int type;
    bool normalized;
    int width;
    char name[32];
};

const VertexAttrib __vaConfig[] ={
    VA_VEC, 3, GL_FLOAT, false, 12, "a_v",
    VA_NORMAL, 3, GL_FLOAT, false, 12, "a_vn",
    VA_COLOR, 4, GL_UNSIGNED_BYTE, true, 4, "a_color",
    VA_TEX0, 3, GL_FLOAT, false, 12, "a_tex0",
};

#endif
