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
#include "docs/Archive.h"

using namespace mco;
using namespace mrd;
using namespace mut;
using namespace mdoc;

extern Archive _archive;


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
    }
    virtual void render() {
        _shader.apply();
        _rd->setUniform(_shader);
        _rd->enableVertexArrays(&_vb, _shader._attribBits);
        _rd->draw(GL_TRIANGLE_FAN, 0, 4);
        _err = glGetError();
    }
};

class T_Shape : public MRenderTestCase
{
    Shape *_shape;
    Shader _shader;
public:
    MT_RENDER_CASE_DECLARE(Shape)
    
    virtual void init() {
        _shape = ShapeFactory::createPyramid();
        _shader.setSource((const char **)VS_MESH, (const char **)PS_MESH);
    }
    virtual void render() {
        _shader.apply();
        _rd->setUniform(_shader);
        _rd->enableVertexArrays(_shape, _shader._attribBits);
        _rd->draw(GL_TRIANGLES, 0, 18);
        _rd->endDraw();
        _err = glGetError();
    }
};

class T_Tex : public MRenderTestCase
{
    Texture2D _tex;
    Texture2D *_tex2;
    VertexBuffer _vb;
    Shader _shader;
    int _tex0;
public:
    MT_RENDER_CASE_DECLARE(Tex)
    virtual void init() {
        NULL;
        unsigned int pixels[512][512];
        for (int i = 0; i < 512; i++) {
            for (int j = 0; j < 512; j++)
                pixels[i][j] = rand();
        }
        _tex.setData(512, 512, pixels);
        _err = glGetError();
        UIImageVertex v[] = {
            -0.5,  0.5, 0, 0, 0,
            -0.5, -0.5, 0, 0, 1,
            0.5, -0.5, 0, 1, 1,
            0.5,  0.5, 0, 1, 0
        };
        _vb.setData(v, sizeof(v), VA_VERTEX | VA_TEX0);
        _shader.setSource((const char **)VS_UI, (const char **)PS_UI);
#ifdef  __MRENDER_IOS__
        long idImage = _archive.openFile("images", "fruit.pvr");
#else
        long idImage = _archive.openFile("images", "image4.dds");
#endif
        int len = _archive.getSize(idImage);
        char *buf = new char[len];
        _archive.read(idImage, buf, len);
        _archive.closeFile(idImage);
        _tex2 = TextureFactory::loadTexture2D(buf, len);
        
    }
    virtual void render() {
        _shader.apply();
        _rd->enableVertexArrays(&_vb, _shader._attribBits);
        _tex2->apply();
        _rd->draw(GL_TRIANGLE_FAN, 0, 4);
        _rd->endDraw();
    }
};


class T_Geometry : public MRenderTestCase
{
    Lines *_lines;
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
        _lines = new Lines(v, 6);
    }
    virtual void render() {
        _rd->draw(_lines);
        _err = glGetError();
    }
};

#endif /* defined(____T_Render__) */
