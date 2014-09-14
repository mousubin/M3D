//
//  vec4.h
//  M3D
//
//  Created by msb on 14-9-11.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#ifndef M3D_vec4_h
#define M3D_vec4_h


namespace MCore {

template<class T>
struct vec4_t
{
    T x, y, z, w;
    vec4_t(float xx, float yy, float zz, float ww){
        x = xx; y = yy; z = zz; w = ww;
    }
    vec4_t(double xx, double yy, double zz, double ww){
        x = xx; y = yy; z = zz; w = ww;
    }
    vec4_t(int xx, int yy, int zz, int ww){
        x = xx; y = yy; z = zz; w = ww;
    }
    vec4_t(unsigned char xx, unsigned char yy, unsigned char zz, unsigned char ww){
        x = xx; y = yy; z = zz; w = ww;
    }
};




typedef vec4_t<int> vec4i;
typedef vec4_t<float> vec4f;
typedef vec4_t<double> vec4d;
typedef vec4f vec4;



｝

#endif
