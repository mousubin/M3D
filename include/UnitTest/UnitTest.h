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
#include <stdarg.h>

namespace mut {

// base test class
    
    // 测试用例
    class MTestObject
    {
    public:
        // 测试函数
        typedef void (MTestObject::*TestFunc)();
        
    };

    class MTestCase : public MTestObject
    {
        std::vector<MTestObject::TestFunc> _list;
    protected:
        std::string _name;  // 测试用例名称
    public:
        MTestCase(const char *name) {
            _name = name;
        }
        const char *name() { return _name.c_str(); }
        // 注册测试用例函数
        void reg(MTestObject::TestFunc f){
            _list.push_back(f);
        }
        
    public:
        // 测试用例初始化
        virtual void init(){};
        // 启动测试用例前的准备函数
        virtual void begin(){};
        // 运行测试用例
        virtual void run(){
            std::vector<MTestObject::TestFunc>::iterator iter;
            for (iter=_list.begin(); iter!=_list.end(); iter++){
                (this->*(*iter))();
            }
        }
        // 测试用例结束的清理函数
        virtual void end(){};
    };
    
    // 测试套件
    class MTestSuite : public MTestObject
    {
    protected:
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
        // 注册测试用例
        void reg(MTestCase *ptc){
            ptc->init();
            _list.push_back(ptc);
        }
        // 记录测试是否成功
        void success(bool b) { _allCount++; if (!b) _errCount++; }
        virtual void begin() {}
        virtual void end() {}
        // 运行测试套件
        virtual void run(){
            log("*** [Test Start] ***\n");
            begin();
            std::vector<MTestCase *>::iterator iter;
            for (iter=_list.begin(); iter!=_list.end(); iter++){
                log("===> TestCase : %s\n", (*iter)->name());
                (*iter)->begin();
                (*iter)->run();
                (*iter)->end();
            }
            end();
            log("*** [ Test End ] ***\nTest Result: count=%d, error=%d.\n", _allCount, _errCount);
        }
        // 日志输出
        void log(const char *fmt, ...){
            va_list args;
            int n;
            va_start(args, fmt);
            char buf[1024];
#ifdef WIN32
			n = vsprintf_s(buf, 1024, fmt, args);
#else
            n = vsprintf(buf, fmt, args);
#endif
            va_end(args);
            std::cout << buf;
        }
    };
    
    
// 带输出信息的测试条件宏
#define MTEST_LOG(logInfo, X, Y)   { MTestSuite &ts=*MTestSuite::getInstance();\
    X; bool b=(Y); ts.success(b); \
    if (Y) MTestSuite::getInstance()->log("\t[Test ok] %s\n", logInfo); \
    else MTestSuite::getInstance()->log("\t[Test error] %s\n", logInfo); }
// 测试条件宏
#define MTEST(X, Y)     MTEST_LOG(#X, X, Y)
    

#define MT_CASES
#define MT_RUN  mut::MTestSuite::getInstance()->run();
    
// 定义用于其他宏内需要使用的测试用例类型
#define MTCaseType(X)   typedef X   TestCaseType

// 注册测试用例：按名称注册，类名为T_名称
#define MT_CASE(X)      MTestSuite::getInstance()->reg(new T_##X);
#define MT_CASE_REG     MT_CASE
// 注册测试用例：指定类名称
#define MT_CASE_CLASS(X)    MTestSuite::getInstance()->reg(new X(#X));

// 注册测试函数
#define MT_ITEM(X)      reg(static_cast<MTestObject::TestFunc>(&TestCaseType::X))
    
// 定义测试用例，形如
// MT_BEGIN(TestCaseName)
// {
//      MT_ITEM(testFunc)
// }
// void testFunc() {
//      ...
// }
// ...
// MT_END
#define MT_BEGIN(X)     class T_##X : public MTestCase {\
                            typedef T_##X TestCaseType;\
                        public: \
                            T_##X() : MTestCase(#X){}\
                            void init()
#define MT_END          };
    
    
    
}

#endif



