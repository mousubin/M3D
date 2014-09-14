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

namespace MUnitTest {
    
    
#define TestCase(X) class TestCase_##X : public MTestCase { \
    typedef TestCase_##X TestCase_Class; \
    void run(){ \
        std::vector<TestItemFunc>::iterator iter;\
        for (iter = _items.begin(); iter != _items.end(); iter++) {\
            (this->*(*iter))();\
        }\
    }\
    void _anonymous_()
#define EndTestCase };
#define TestItem(X) } public: void TestItem_##X() { \
    reg(static_cast<TestItemFunc>(&TestCase_Class::TestItem_##X));

    
    class MTestCase
    {
    public:
        typedef void (MTestCase::*TestItemFunc)(void);
        std::vector<TestItemFunc> _items;
    public:
        void reg(TestItemFunc func) {
            _items.push_back(func);
        }
        
    };
    
    class MTestSuite
    {
    };
    

}

#endif
