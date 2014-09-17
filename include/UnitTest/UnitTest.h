//
//  UnitTest.h
//  
//
//  Created by msb on 14-9-13.
//
//

#ifndef _UnitTest_h
#define _UnitTest_h

#include <vector>
#include <iostream>

namespace mut {

// base test class
    
    class MTestObject
    {
    public:
        typedef void (MTestObject::*TestFunc)();
        
    };

    class MTestCase : public MTestObject
    {
        std::vector<MTestObject::TestFunc> _list;
    protected:
        std::string _name;
    public:
        void reg(MTestObject::TestFunc f){
            _list.push_back(f);
        }
    public:
        virtual void init(){};
        virtual void begin(){};
        virtual void run(){
            std::vector<MTestObject::TestFunc>::iterator iter;
            for (iter=_list.begin(); iter!=_list.end(); iter++){
                (this->*(*iter))();
            }
        }
        virtual void end(){};
    };
    
    class MTestSuite : public MTestObject
    {
        std::vector<MTestCase *> _list;
        int _allCount;
        int _errCount;
    public:
        MTestSuite(){
            _allCount = 0;
            _errCount = 0;
        }
        static MTestSuite *getInstance(){
            static MTestSuite *pts = NULL;
            if (pts == NULL)
                pts = new MTestSuite;
            return pts;
        }
        void reg(MTestCase *ptc){
            ptc->init();
            _list.push_back(ptc);
        }
        void success(bool b) { _allCount++; if (!b) _errCount++; }
        void run(){
            log("*** [Test Start] ***\n");
            std::vector<MTestCase *>::iterator iter;
            for (iter=_list.begin(); iter!=_list.end(); iter++){
                (*iter)->begin();
                (*iter)->run();
                (*iter)->end();
            }
            log("*** [ Test End ] ***\nTest Result: count=%d, error=%d.\n", _allCount, _errCount);
        }
        void log(const char *fmt, ...){
            va_list args;
            int n;
            va_start(args, fmt);
            char buf[4096];
            n = vsprintf(buf, fmt, args);
            va_end(args);
            std::cout << buf;
        }
    };
    

#define MTEST(X, Y)   { MTestSuite &ts=*MTestSuite::getInstance();\
    X; bool b=(Y); ts.success(b); \
    if (Y) MTestSuite::getInstance()->log("[Test ok] %s\n", #X); \
    else MTestSuite::getInstance()->log("[Test error] %s\n", #X); }
    
#define MTEST_LOG(log, X, Y)
    
#define MT_CASES
#define MT_RUN  mut::MTestSuite::getInstance()->run();
    
#define MTCaseType(X)   typedef X   TestCaseType

#define MT_CASE(X)      MTestSuite::getInstance()->reg(new T_##X);
#define MT_CASE_CLASS(X)    MTestSuite::getInstance()->reg(new X);
#define MT_ITEM(X)      reg(static_cast<MTestObject::TestFunc>(&TestCaseType::X))
    
#define MT_BEGIN(X)     class T_##X : public MTestCase { typedef T_##X TestCaseType; public: void init()
#define MT_END          };
    
    
    
}

#endif
