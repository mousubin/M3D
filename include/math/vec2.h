//  
//  vec2.h
//  M3D
//
//  Created by msb on 14-9-9.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#ifndef M3D_vec2_h
#define M3D_vec2_h


namespace mco {

template<class T>
struct vec2_t
{
    union { T x; T u; };
    union { T y; T v; };
    vec2_t(float xx, float yy){
        x = xx; y = yy;
    }
    vec2_t(double xx, double yy){
        x = xx; y = yy;
    }
};


typedef vec2_t<int> vec2i;
typedef vec2_t<float> vec2f;
typedef vec2_t<double> vec2d;
typedef vec2f vec2;
    

};

#endif
