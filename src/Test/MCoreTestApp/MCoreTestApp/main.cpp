//
//  main.cpp
//  MCoreTestApp
//
//  Created by msb on 14-9-13.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "UnitTest/UnitTest.h"
#include "T_vec2.h"
#include "T_vec3.h"
#include "T_vec4.h"
#include "T_mat4.h"

int main(int argc, const char * argv[])
{
    MT_CASES
    {
        MT_CASE(Vec2);
        MT_CASE(Vec3);
        MT_CASE(Vec4);
        MT_CASE_REG(Mat4);
    }
    
    MT_RUN;
    return 0;
}

