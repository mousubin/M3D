//
//  T_Render.h
//  
//
//  Created by msb on 14-9-18.
//
//

#ifndef ____T_Render__
#define ____T_Render__

#include <iostream>

#include "math/vec3.h"
#include "Render/Render.h"
#include "UnitTest/UnitTestRender.h"

using namespace mco;
using namespace mrd;
using namespace mut;

class T_Base : public MRenderTestCase
{
public:
    MT_RENDER_CASE_DECLARE(Base)
    virtual void render() { // clear blue color
        _rd->clearColor(0xff0000);
        _rd->clear(ColorBufferBit | DepthBufferBit);
    }
};

class T_Vertex : public MRenderTestCase
{
    VertexBuffer _vb;
    Shader _shader;
    int _mvp;
public:
    MT_RENDER_CASE_DECLARE(Vertex)
    
    virtual void init() {
        ColorVertex v[] ={
            -0.5,  0.5, 0, 0x0000ff,
            -0.5, -0.5, 0, 0x00ff00,
            0.5, -0.5, 0, 0xff0000,
            0.5,  0.5, 0, 0xffffff
        };
     
        _vb.setData(v, sizeof(v), VA_VEC | VA_COLOR);
        _shader.setSource((const char **)VS_COLOR, (const char **)PS_COLOR);
        _vb.bindAttrib(_shader);
        _shader.make();
        _mvp = _shader.getUniform("u_mvp");
    }
    virtual void render() {
       // init();
        _vb.apply();
        _shader.apply();
        mat4f mPrj, mView;
        mPrj.makePerspertive(1.5, 0.5, 0.1, 1000);
        mView.makeTranslation(0, 0, -5);
        mat4f mvp = mat4f::multiply(mPrj, mView);
        //mvp.makeIdentity();
        _shader.setUniform(_mvp, mvp);
        
        _rd->draw(GL_TRIANGLE_FAN, 0, 4);
        _err = glGetError();
    }
};

#endif /* defined(____T_Render__) */
