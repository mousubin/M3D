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
        virtual void update() {}
        virtual void render() {}
    };
    
    class MRenderTestSuite : public MTestSuite
    {
        mrd::Render *_rd;
    public:
        static MRenderTestSuite *getInstance(){
            static MRenderTestSuite *pts = NULL;
            if (pts == NULL)
                pts = new MRenderTestSuite;
            return pts;
        }
        void setRender(mrd::Render *rd) { _rd = rd; }
        virtual void update() {
            std::vector<MTestCase *>::iterator iter;
            for (iter=_list.begin(); iter!=_list.end(); iter++){
                MRenderTestCase *pCase = dynamic_cast<MRenderTestCase *>(*iter);
                pCase->update();
            }
        }
        virtual void render() {
            _rd->beginScene();
            _rd->clearColor(0x800000);
            _rd->clearDepth(1.0f);
            _rd->clear(mrd::ColorBufferBit | mrd::DepthBufferBit);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glDepthFunc(GL_LEQUAL);
            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);
            
            static float _radians = 0;
            _radians += 0.01f;
            mco::mat4f mPrj, mView, mWorld;
            float d = 2.0f;
            float aspect = (float)_rd->_viewWidth / _rd->_viewHeight;
            mPrj.makePerspertive(3.1415f / 3, aspect, 0.1f, 1000);
            mView.makeLookAt(d * cos(_radians), d, d * sin(_radians), 0, 0, 0, 0, 1, 0);
            mWorld.makeIdentity();
            _rd->setMatrix(&mPrj, &mView, &mWorld);
            
            std::vector<MTestCase *>::iterator iter;
            for (iter=_list.begin(); iter!=_list.end(); iter++){
                MRenderTestCase *pCase = dynamic_cast<MRenderTestCase *>(*iter);
                pCase->render();
            }
            _rd->endScene();
            _rd->show();
        }
        // 运行测试套件
        virtual void run(){
            log("*** [Test Start] ***\n");
            update();
            render();
            glFlush();
            log("*** [ Test End ] ***\nTest Result: count=%d, error=%d.\n", _allCount, _errCount);
        }
    };
    
    // 注册测试用例：按名称注册，类名为T_名称
#define MT_RENDER_CASE(X, RENDER)      MRenderTestSuite::getInstance()->reg(new T_##X(RENDER));
#define MT_RENDER_CASE_DECLARE(X)      T_##X(mrd::Render *rd) : MRenderTestCase(#X, rd){}
#define MT_RENDER_RUN  mut::MRenderTestSuite::getInstance()->run();
    
}

#endif




