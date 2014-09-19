//
//  T_Render.cpp
//  
//
//  Created by msb on 14-9-18.
//
//

#include "T_Render.h"


void T_Render::tBase()
{
    _rd->clearColor(0xffff0000);
    _rd->clear(ColorBufferBit | DepthBufferBit);
}


void T_Render::tVertex()
{
    struct Vertex
    {
        float x, y, z;
        unsigned int cr;
    } v[] ={
        -0.5,  0.5, 0, 0xff0000ff,
        -0.5, -0.5, 0, 0xff00ff00,
         0.5, -0.5, 0, 0xffff0000,
         0.5,  0.5, 0, 0xffffffff
    };
    VertexBuffer vb;
    vb.setData(v, sizeof(v), VA_VEC | VA_COLOR);
    Shader shader;
    shader.setSource((const char **)VS_CODE, (const char **)PS_CODE);
    vb.bindAttrib(shader);
    shader.make();
    
    vb.apply();
    shader.apply();
    _rd->draw(GL_TRIANGLE_FAN, 0, 4);
    int err = glGetError();
    
}