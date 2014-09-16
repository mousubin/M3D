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
#include "T_vec3.h"

class MTCaseBase
{
public:
    typedef void (MTCaseBase::*TestFunc)(void);
    void init();
    void reg();
    void run();
};

class TVec : public MTCaseBase
{
public:
    void init(){
        reg();
    }
    void test1(){
        
    }
};

//template <class T>
class MTCase
{

public:
    typedef void (MTCase::*TestOneFunc)(void);
    std::vector<MTCase::TestOneFunc> _list;
    MTCase(){
    }
    virtual void init() = 0;
    void Test1(){
        
    }
    void reg(MTCase::TestOneFunc f){
        _list.push_back(f);
    }
    void run(){
        std::vector<MTCase::TestOneFunc>::iterator iter;
        for (iter=_list.begin(); iter!=_list.end(); iter++){
            (this->*(*iter))();
        }
    }
};
#define TCaseOne(X)  reg(static_cast<MTCase::TestOneFunc>(&TT::X))
#define TCaseBegin(X)    class MTCase##X : public MTCase { typedef MTCase##X TT; public: void init()
#define TCaseEnd    };

TCaseBegin(Vec3)
{
    TCaseOne(f1);
    TCaseOne(f2);
}
void f1()
{
    std::cout << "test1\n";
}
void f2()
{
    std::cout << "test2\n";
}
TCaseEnd

int main(int argc, const char * argv[])
{
    T_Vec3 t;
    t.init();
    t.run();
    MTCaseVec3 vvv;
    vvv.init();
    vvv.run();
   // MHandler<1> h;
    // insert code here...
    std::cout << "MCoreTest start!\n";
    mut::MTestSuite::getInstance()->run();
    std::cout << "MCoreTest end!\n";
    auto f = [] (int x, int y) { return x + y; };
    int i = f(1,2);
    return 0;
}

