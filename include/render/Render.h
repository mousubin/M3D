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
    public:
        void setTarget(Target *target){
            target->active();
        }
        void beginScene(){}
        void endScene(){}
        void show() {
            glFlush();
        }
    public:
        void clear(int bufferBit){
            glClear(bufferBit);
        }
        void clearColor(unsigned int color){
            Color cr;
            cr.fromUINT(color);
            glClearColor(cr.r, cr.g, cr.b, cr.a);
        }
        void draw(int mode, int first, int count) {
            glDrawArrays(mode, first, count);
        }
    };
    
    class Buffer;
    
}



#endif
