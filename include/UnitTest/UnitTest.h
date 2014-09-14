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
    
    
#define TestCase(X) class TestCase_##X : public MTestCase
#define TestItem(X) public: void TestItem_##X()
    //{ reg(TestItem#X); }
    
    class MTestCase
    {
    public:
        typedef void (*TestItemFunc)(void);
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
