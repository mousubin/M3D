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
     
        _vb.setData(v, sizeof(v), VA_VERTEX | VA_COLOR);
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
        mPrj.makePerspertive(1.5f, 0.5f, 0.1f, 1000);
        mView.makeTranslation(0, 0, -5);
        mat4f mvp = mat4f::multiply(mPrj, mView);
        //mvp.makeIdentity();
        _shader.setUniform(_mvp, mvp);
        
        _rd->draw(GL_TRIANGLE_FAN, 0, 4);
        _err = glGetError();
    }
};


class T_Shape : public MRenderTestCase
{
    Shape *_shape;
    Shader _shader;
    int _mvp, _mNormal;
public:
    MT_RENDER_CASE_DECLARE(Shape)
    
    virtual void init() {
        _shape = ShapeFactory::createPyramid();
        _shader.setSource((const char **)VS_MESH, (const char **)PS_MESH);
        _shape->bindAttrib(_shader);
        _shader.make();
        _mvp = _shader.getUniform("u_mvp");
        _mNormal = _shader.getUniform("u_mNormal");
    }
    virtual void render() {
        // init();
        static float radians = 0;
        radians += 0.01f;
        _shape->apply();
        _shader.apply();
        mat4f mPrj, mWorld;
        mPrj.makePerspertive(1.5f, 0.5f, 0.1f, 1000);
        mat4f mR;
        mR.makeRotation(radians, 0.0f, 1.0f, 0.0f);
        mWorld.makeTranslation(0, 0, -5);
        mWorld = mat4f::multiply(mWorld, mR);
        
        mat4f mView;
        float d = 2.0f;
        mView.makeLookAt(d * cos(radians), d, d * sin(radians), 0, 0, 0, 0, 1, 0);
        mat3f mNormal;
        mView.getMatrix3(mNormal);
        mNormal.invertAndTranspose();
        
        mat4f mvp = mat4f::multiply(mPrj, mView);
        //mvp.makeIdentity();
        _shader.setUniform(_mvp, mvp);
        //mNormal.makeIdentity();
        _shader.setUniform(_mNormal, mNormal);
        
        _rd->draw(GL_TRIANGLES, 0, 18);
        _err = glGetError();
    }
};

class T_Tex : public MRenderTestCase
{
    Texture2D _tex;
    VertexBuffer _vb;
    Shader _shader;
    int _tex0;
public:
    MT_RENDER_CASE_DECLARE(Tex)
    virtual void init() {
        unsigned int pixels[512][512];
        for (int i = 0; i < 512; i++) {
            for (int j = 0; j < 512; j++)
                pixels[i][j] = rand();
        }
        _tex.setData(512, 512, pixels);
        _err = glGetError();
        UIImageVertex v[] = {
            -0.5,  0.5, 0, 0, 0,
            -0.5, -0.5, 0, 1, 0,
            0.5, -0.5, 0, 1, 1,
            0.5,  0.5, 0, 0, 1
        };
        _vb.setData(v, sizeof(v), VA_VERTEX | VA_TEX0);
        _shader.setSource((const char **)VS_UI, (const char **)PS_UI);
        _vb.bindAttrib(_shader);
        _shader.make();
        _tex0 = _shader.getUniform("u_tex0");
        _shader.setTexture(_tex0, GL_TEXTURE0);
        
    }
    virtual void render() {
        _vb.apply();
        _shader.apply();
        _tex.apply();
        _rd->draw(GL_TRIANGLE_FAN, 0, 4);
    }
};


class T_Geometry : public MRenderTestCase
{
    Lines *_pl;
public:
    MT_RENDER_CASE_DECLARE(Geometry)
    virtual void init() {
        ColorVertex v[] = {
              0,   0,   0,  0xff0000ff,
            100,   0,   0,  0xff0000ff,
              0,   0,   0,  0xff00ff00,
              0, 100,   0,  0xff00ff00,
              0,   0,   0,  0xffff0000,
              0,   0, 100,  0xffff0000
        };
        _pl = new Lines(v, 4);
    }
    virtual void render() {
       // _rd->drawLine();
       // _rd->drawGeometry();
    }
};

#endif /* defined(____T_Render__) */
