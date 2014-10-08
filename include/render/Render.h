//
//  render.h
//  
//
//  Created by msb on 14-9-17.
//
//

#ifndef _render_h
#define _render_h

#include "RenderTypes.h"
#include "Vertex.h"
#include "Shape.h"
#include "Shader.h"
#include "Texture.h"
#include "math/vec4.h"

#include "Geometry.h"

namespace mrd {
    
    class Target
    {
    public:
        virtual void active() = 0;
    };
    
    class TargetFactory
    {
    public:
        virtual Target *createTarget() = 0;
    };
    
    class Render;
    class RenderSystem
    {
        TargetFactory *_tf;
        Render *_rd;
    public:
        static RenderSystem *getInstance(){
            static RenderSystem *prs = NULL;
            if (prs == NULL){
                prs = new RenderSystem;
            }
            return prs;
        }
        void installTargetFactory(TargetFactory *ptf){
            _tf = ptf;
        }
        Render* getRender(){ return _rd; }
    };
    
    class Render
    {
        mco::mat4f _mPrj, _mView, _mWorld;
        mco::mat4f _mvp;
        mco::mat3f _mNormal;
        int _nVertexArrays;
    public:
        int _viewWidth, _viewHeight;
        std::string _openGLInfo;
    public:
        Render() {
            _nVertexArrays = 0;
            mco::mat4f m;
            m.makeIdentity();
            setMatrix(&m, &m, &m);
            _viewWidth = _viewHeight = 1.0f;
        }
        void setTarget(Target *target){
            target->active();
        }
        void beginScene(){}
        void endScene(){}
        void show() { glFlush(); }
    public:
        void setMatrix(mco::mat4f *mPrj, mco::mat4f *mView, mco::mat4f *mWorld) {
            if (mPrj)   _mPrj = *mPrj;
            if (mView)  _mView = *mView;
            if (mWorld) _mWorld = *mWorld;
            _mvp = _mPrj * _mView * _mWorld;
            _mView.getMatrix3(_mNormal);
            _mNormal.invertAndTranspose();
        }
    public:
        void init() {
            getOpenGLInfo();
        }
        void getOpenGLInfo() {
            _openGLInfo = (char *)glGetString(GL_EXTENSIONS);
        }
        void clear(int bufferBit){
            glClear(bufferBit);
        }
        void clearColor(unsigned int color){
            Color cr;
            cr.fromUINT(color);
            glClearColor(cr.r, cr.g, cr.b, cr.a);
        }
        void clearDepth(float f) {
#ifdef __MRENDER_IOS__
            glClearDepthf(f);
#else
            glClearDepth(f);
#endif
        }
        void setViewport(int x, int y, int width, int height) {
            _viewWidth = width;
            _viewHeight = height;
            glViewport(x, y, width, height);
        }
        void enableVertexArrays(VertexBuffer *vb, unsigned int attribBit) {
            vb->apply(attribBit);
            _nVertexArrays = vb->_nCurVertexArrays;
        }
        void endDraw() {
            for (int i = 0; i < _nVertexArrays; i++)
                glDisableVertexAttribArray(i);
            glUseProgram(0);
        }
        void setUniform(Shader &shader) {
            for (int i = 0; i < shader._nUniforms; i++) {
                int j = shader._uniforms[i];
                int loc = shader._uniformLocations[i];
                switch (__standardUniform[j].uniform) {
                    case U_MVP:
                        shader.setUniform(loc, _mvp);
                        break;
                    case U_NORMAL_MATRIX:
                        shader.setUniform(loc, _mNormal);
                        break;
                }
            }
        }
        void draw(int mode, int first, int count) {
            glDrawArrays(mode, first, count);
        }
        void draw(RenderObject *ro) {
            ro->render(this);
            endDraw();
        }
    };
    
    class Buffer;
    
}



#endif
