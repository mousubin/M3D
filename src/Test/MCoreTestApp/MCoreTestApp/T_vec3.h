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

using namespace mco;
using namespace mut;



class T_Vec3 : public MTestCase
{
public:
    void init(){
        reg(static_cast<MTestObject::TestFunc>(&T_Vec3::t0));
    }
    void t0(){
        vec3f v1(1.0f, 2.0f, 3.0f), v2(2, 3, 4);
        vec3d v3;
        v3 = v1;
        MTEST(v3 = v1, (v3.x = v1.x) && (v3.y == v1.y) && (v3.z = v1.z));
//        v3 = v1 + v2;
//        v3 = v1 - v2;
//        v3 = v1 * v2;
//        v3 = v1 ^ v2;
//        v3 = v1
//        v3 = v1;
//        v3 ＋＝ v2;
//        v3 = v1;
//        v3.sub(v2);
//        v3 = v1;
//        v3.multi(v2);
//        v3 = v1;
//        v3.nomalize();
//        v3 = v1;
    }
};



#endif /* defined(__MCoreTestApp__T_vec3__) */
