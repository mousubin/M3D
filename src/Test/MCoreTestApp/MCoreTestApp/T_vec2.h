//
//  T_vec2.h
//  MCoreTestApp
//
//  Created by msb on 14-9-17.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#ifndef __MCoreTestApp__T_vec2__
#define __MCoreTestApp__T_vec2__

#include "UnitTest/UnitTest.h"
#include "math/vec2.h"

using namespace mco;
using namespace mut;

#define MTEST_ITEM(X)   reg(static_cast<MTestObject::TestFunc>(&TestCaseType::X))

#define MTCaseBegin(X)    class MTCase##X : public MTestCase { typedef MTCase##X TestCaseType; public: void init()
#define MTCaseEnd    };

MTCaseBegin(Vec2)
{
    MTEST_ITEM(f1);
    MTEST_ITEM(f2);
}
void f1()
{
    std::cout << "test1\n";
}
void f2()
{
    std::cout << "test2\n";
}
MTCaseEnd


#endif /* defined(__MCoreTestApp__T_vec2__) */
