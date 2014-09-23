//
//  T_mat4.h
//  MCoreTestApp
//
//  Created by msb on 14-9-23.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#ifndef __MCoreTestApp__T_mat4__
#define __MCoreTestApp__T_mat4__

#include <stdio.h>
#include "math/math.h"
#include "UnitTest/UnitTest.h"

using namespace mco;
using namespace mut;

MT_BEGIN(Mat4)
{
    MT_ITEM(base);
    MT_ITEM(perspertive);
    MT_ITEM(translation);
}

void base()
{
    mat4f m = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

void perspertive()
{
    mat4f m;
    mat4f mm = {
        2.7861917, 0, 0, 0,
        0, 1.56968558, 0, 0,
        0, 0, -1.002002, -1,
        0, 0, -0.2002002, 0
    };
    MTEST(m.makePerspertive(Angle2Radian(65.0f), 0.563380301f, 0.1f, 100.0f), m == mm);
}

void translation()
{
    mat4f m;
    mat4f mm = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 2, 3, 0,
    };
    MTEST(m.makeTranslation(1, 2, 3), m == mm);
}

MT_END;








#endif /* defined(__MCoreTestApp__T_mat4__) */
