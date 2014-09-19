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

using namespace mco;
using namespace mrd;

class RenderTestCase
{
public:
    virtual void init() {};
    virtual void update() {};
    virtual void render() {}
};

class T_Render : public RenderTestCase
{
    Target *_target;
    Render *_rd;
public:
    T_Render(Target *target){
        _target = target;
        RenderSystem *rs = RenderSystem::getInstance();
        _rd = rs->getRender();
    }
    void run(){
        _rd->beginScene();
        
        tBase();
        tVertex();
        
        _rd->endScene();
        _rd->show();
    }
    void tBase();
    void tVertex();
};
    
class RenderTestSuite
{
    T_Render *_case;
public:
    static RenderTestSuite *getInstance(Target *target){
        static RenderTestSuite *rts = NULL;
        if (rts == NULL){
            rts = new RenderTestSuite;
            rts->init(target);
        }
        return rts;
    }
    void init(Target *target){
        _case = new T_Render(target);
        
    }
    void run(){
        _case->run();
    }
};

#endif /* defined(____T_Render__) */
