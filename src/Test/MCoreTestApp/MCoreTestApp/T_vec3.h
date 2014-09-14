//
//  T_vec3.h
//  MCoreTestApp
//
//  Created by msb on 14-9-13.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#ifndef __MCoreTestApp__T_vec3__
#define __MCoreTestApp__T_vec3__


#include "UnitTest/UnitTest.h"
#include "math/vec3.h"

using namespace MCore;
using namespace MUnitTest;


TestCase(vec3)
{
    TestItem(0) {
          vec3f v1(1.0f, 2.0f, 3.0f), v2(2, 3, 4);
//        vec3d v3;
//        v3 = v1;
//        v3 = v1 + v2;
//        v3 = v1 - v2;
//        v3 = v1 * v2;
//        v3 = v1 ^ v2;
//        v3 = v1
//        v3 = v1;
//        v3.add(v2);
//        v3 = v1;
//        v3.sub(v2);
//        v3 = v1;
//        v3.multi(v2);
//        v3 = v1;
//        v3.nomalize();
//        v3 = v1;
    }
    TestItem(1) {
    }
}
EndTestCase


TestCase(vec4) {
    TestItem(0) {
        vec3f v1(1.0f, 2.0f, 3.0f), v2(2, 3, 4);

    }
    TestItem(1) {
    }
}
EndTestCase


#endif /* defined(__MCoreTestApp__T_vec3__) */
