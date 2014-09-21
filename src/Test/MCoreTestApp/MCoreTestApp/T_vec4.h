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


class T_Vec4 : public MTestCase
{ 
    MTCaseType(T_Vec4);
public:
    T_Vec4() : MTestCase("Vec4"){}
    virtual void init(){
        MT_ITEM(t0);
    }
    void t0(){
        vec4f v1;
        std::cout << "\tok" << std::endl;
    }
};


#endif /* defined(__MCoreTestApp__T_vec4__) */
