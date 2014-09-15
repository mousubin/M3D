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




int main(int argc, const char * argv[])
{
   // MHandler<1> h;
    // insert code here...
    std::cout << "MCoreTest start!\n";
    mut::MTestSuite::getInstance()->run();
    std::cout << "MCoreTest end!\n";
    auto f = [] (int x, int y) { return x + y; };
    int i = f(1,2);
    return 0;
}

