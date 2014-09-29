//
//  UnitTestRender.h
//  
//
//  Created by msb on 14-9-21.
//
//

#ifndef _UnitTestRender_h
#define _UnitTestRender_h


#include "UnitTest.h"
#include "Render/Render.h"

namespace mut {
    

    class MRenderTestCase : public MTestCase
    {
    protected:
        mrd::Render *_rd;
    public:
        int _err;
    public:
        MRenderTestCase(const char *name, mrd::Render *rd) : MTestCase(name), _rd(rd), _err(0) {}
        virtual void run() {
            update();
            _rd->beginScene();
            _rd->clearColor(0x800000);
            _rd->clear(mrd::ColorBufferBit | mrd::DepthBufferBit);
            render();
            _rd->endScene();
            _rd->show();
        }
        virtual void update() {}
        virtual void render() {}
    };
    
    class MRenderTestSuite : public MTestSuite
    {
    public:
    };
    
    // 注册测试用例：按名称注册，类名为T_名称
#define MT_RENDER_CASE(X, RENDER)      MTestSuite::getInstance()->reg(new T_##X(RENDER));
#define MT_RENDER_CASE_DECLARE(X)      T_##X(mrd::Render *rd) : MRenderTestCase(#X, rd){}
}

#endif




