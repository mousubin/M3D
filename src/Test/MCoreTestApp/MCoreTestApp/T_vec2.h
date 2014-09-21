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



MT_BEGIN(Vec2)
{
    MT_ITEM(f1);
    MT_ITEM(f2);
}
void f1()
{
    std::cout << "\ttest1\n";
}
void f2()
{
    std::cout << "\ttest2\n";
}
MT_END


#endif /* defined(__MCoreTestApp__T_vec2__) */
