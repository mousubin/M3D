//
//  T_vec4.h
//  MCoreTestApp
//
//  Created by msb on 14-9-17.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#ifndef __MCoreTestApp__T_vec4__
#define __MCoreTestApp__T_vec4__

#include "UnitTest/UnitTest.h"
#include "math/vec4.h"

using namespace mco;
using namespace mut;

#define MTEST_CASE(X)   typedef X   TestCaseType
#define MTEST_ITEM(X)   reg(static_cast<MTestObject::TestFunc>(&TestCaseType::X))

class T_Vec4 : public MTestCase
{ 
    MTEST_CASE(T_Vec4);
public:
    void init(){
        MTEST_ITEM(t0);
    }
    void t0(){
        vec4f v1;
    }
};


#endif /* defined(__MCoreTestApp__T_vec4__) */
