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

    #define MTEST(X, Y)   X; \
       if (Y) MTestSuite::getInstance()->log("[Test] %s Ok\n", #X); \
        else MTestSuite::getInstance()->log("Error");
    
    class MTestObject
    {
    public:
        typedef void (MTestObject::*TestFunc)();
        
    };

    class MTestCase : public MTestObject
    {
        std::vector<MTestObject::TestFunc> _list;
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
    public:
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
        void run(){
            std::vector<MTestCase *>::iterator iter;
            for (iter=_list.begin(); iter!=_list.end(); iter++){
                (*iter)->begin();
                (*iter)->run();
                (*iter)->end();
            }
        }
        void log(const char *Format, ...){
            
            std::cout << Format;
        }
    };
    
//#define TestCase(X) \
//    class TestCase_##X : public MTestCase \
//    { \
//    public: \
//        typedef TestCase_##X TestCase_Class; \
//        TestCase_##X() { \
//             \
//        } \
//        void run(){ \
//            std::vector<TestItemFunc>::iterator iter;\
//            for (iter = _items.begin(); iter != _items.end(); iter++) {\
//                (this->*(*iter))();\
//            }\
//    }\
//    void _anonymous_()
//#define EndTestCase(X) }; \
//    const TestCase_##X *__tc_##X = new TestCase_##X; MTestSuite::getInstance()->reg(__tc_##X);
//    
//#define TestItem(X) } public: void TestItem_##X() { \
//    reg(static_cast<TestItemFunc>(&TestCase_Class::TestItem_##X));
//
//#define TestOne(X, Y)   X; \
//    if (Y) MTestSuite::getInstance()->log("Ok"); \
//    else MTestSuite::getInstance()->log("Error");

//    class MTestCase
//    {
//    public:
//        typedef void (MTestCase::*TestItemFunc)(void);
//        std::vector<TestItemFunc> _items;
//    public:
//        void reg(TestItemFunc func) {
//            _items.push_back(func);
//        }
//        void run(){
//            std::vector<TestItemFunc>::iterator iter;
//            for (iter = _items.begin(); iter != _items.end(); iter++){
//                (this->*(*iter))();
//            }
//        }
//        void destroy(){
//            delete this;
//        }
//    };
//    
//    class MTestSuite
//    {
//        std::vector<MTestCase *> _cases;
//    public:
//        ~MTestSuite(){
//            std::vector<MTestCase *>::iterator iter;
//            for (iter = _cases.begin(); iter != _cases.end(); iter++){
//                (*iter)->destroy();
//            }
//        }
//        static MTestSuite *getInstance(){
//            static MTestSuite *pMTS = NULL;
//            if (pMTS == NULL)
//                pMTS = new MTestSuite;
//            return pMTS;
//        }
//        void log(const char *Format, ...){
//            std::cout << Format;
//        }
//        void run(){
//            std::vector<MTestCase *>::iterator iter;
//            for (iter = _cases.begin(); iter != _cases.end(); iter++){
//                (*iter)->run();
//            }
//        }
//        void reg(MTestCase *pCase){
//            _cases.push_back(pCase);
//        }
//    };
//    
//    template <MTestCase *ptc, MTestCase::TestItemFunc f>
//    class MTestCaseItemHandler
//    {
//        std::string _str;
//        int _n;
//        MTestCase::TestItemFunc _f;
//    public:
//        MTestCaseItemHandler()
//        {
//            ptc->reg(f);
//        }
//    };
//    
//    class MHandler
//    {
//    public:
//        int operator()(){
//            return 1;
//        }
//    };
//    
//#define TestCase(X) \
//    class TestCase_##X : public MTestCase \
//    { \
//    public: \
//        typedef TestCase_##X TestCase_Class; \
//        const char *_name; \
//        TestCase_##X() : _name(#X) { \
//            MTestSuite::getInstance()->reg(this);\
//        } \
//        void run(){ \
//            std::vector<TestItemFunc>::iterator iter;\
//            for (iter = _items.begin(); iter != _items.end(); iter++) {\
//            (this->*(*iter))();\
//        }\
//    }\
//    void _anonymous_()
//    
//#define EndTestCase(X) }; \
//    const TestCase_##X *__tc_##X = new TestCase_##X;
//    
//    
//#define TestItem(X) } \
//    public: void TestItem_##X() { \
//    reg(static_cast<TestItemFunc>(&TestCase_Class::TestItem_##X));
//    
//#define TestOne(X, Y)   X; \
//    if (Y) MTestSuite::getInstance()->log("Ok"); \
//    else MTestSuite::getInstance()->log("Error");

}

#endif
