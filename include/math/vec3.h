//
//  vec3.h
//  M3D
//
//  Created by msb on 14-9-9.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#ifndef M3D_vec3_h
#define M3D_vec3_h

#include <math.h>

namespace mco {

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
        vec3_t &operator = (vec3_t<float> &v){
            x = v.x; y = v.y; z = v.z;
            return *this;
        }
        vec3_t &operator = (vec3_t<double> &v){
            x = v.x; y = v.y; z = v.z;
            return *this;
        }
        vec3_t &operator = (vec3_t<int> &v){
            x = v.x; y = v.y; z = v.z;
            return *this;
        }
        
        vec3_t & operator += (vec3_t &v) {
            x += v.x; y += v.y; z += v.z;
            return *this;
        }
        
        vec3_t & operator -= (vec3_t &v) {
            x -= v.x; y -= v.y; z -= v.z;
            return *this;
        }
        vec3_t & operator - () {
            x = -x; y = -y; z = -z;
            return *this;
        }
        
        T length() {
            return (T)sqrt(x * x + y * y + z * z);
        }
        void normalize() {
            float scale = 1.0f / length();
            x *= scale;
            y *= scale;
            z *= scale;
        }
    };
    
    template<class T>
    inline T operator * (vec3_t<T> &left, vec3_t<T> &right) {
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }

    template<class T>
    inline vec3_t<T> &operator ^ (vec3_t<T> &left, vec3_t<T> &right) {
        static vec3_t<T> v;
        v.x = left.y * right.z - left.z * right.y;
        v.y = left.z * right.x - left.x * right.z;
        v.z = left.x * right.y - left.y * right.x;
        return v;
    }
    
    template<class T>
    inline vec3_t<T> & operator + (vec3_t<T> &left, vec3_t<T> &right) {
        static vec3_t<T> v;
        v.x = left.x + right.x;
        v.y = left.y + right.y;
        v.z = left.z + right.z;
        return v;
    }
    
    template<class T>
    inline vec3_t<T> operator - (vec3_t<T> &left, vec3_t<T> &right) {
        static vec3_t<T> v;
        v.x = left.x - right.x;
        v.y = left.y - right.y;
        v.z = left.z - right.z;
        return v;
    }
    
    typedef vec3_t<int> vec3i;
    typedef vec3_t<float> vec3f;
    typedef vec3_t<double> vec3d;
    typedef vec3f vec3;
    
    

}

#endif
