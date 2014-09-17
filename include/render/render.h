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

#ifdef __MRENDER_IOS__
#include <OpenGLES/ES1/gl.h>
#else
#include <OpenGL/gl.h>
#endif

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
    
    class RenderSystem
    {
        TargetFactory *_tf;
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
    };
    
    class Render
    {
    public:
        void setTarget(Target *target){
            target->active();
        }
        void beginScene(){}
        void endScene(){}
        void clear() {
            glClearColor(1.0f, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        void show() {
            glFlush();
        }
    };
    
    class Buffer;
    
}



#endif
