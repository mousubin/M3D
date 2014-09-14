//
//  vec3.h
//  M3D
//
//  Created by msb on 14-9-9.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#ifndef M3D_vec3_h
#define M3D_vec3_h


namespace MCore {

template<class T>
struct vec3_t
{
    T x, y, z;
    vec3_t(){}
    vec3_t(float xx, float yy, float zz){
        x = xx; y = yy; z = zz;
    }
    vec3_t(double xx, double yy, double zz){
        x = xx; y = yy; z = zz;
    }
    vec3_t(int xx, int yy, int zz){
        x = xx; y = yy; z = zz;
    }
    vec3_t(unsigned char xx, unsigned char yy, unsigned char zz){
        x = xx; y = yy; z = zz;
    }
};

    
typedef vec3_t<int> vec3i;
typedef vec3_t<float> vec3f;
typedef vec3_t<double> vec3d;
typedef vec3f vec3;
    
    

}

#endif
