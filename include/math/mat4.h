//
//  Matrix4.h
//  
//
//  Created by msb on 14-9-23.
//
//

#ifndef _Matrix4_h
#define _Matrix4_h

#include <math.h>
#include "vec3.h"
#include "mat3.h"

namespace mco {


template<class T>
union mat4_t
{
    struct
    {
        T m00, m01, m02, m03;
        T m10, m11, m12, m13;
        T m20, m21, m22, m23;
        T m30, m31, m32, m33;
    };
    T m[16];
    
    operator const T *() { return m; };
    bool operator == (mat4_t &m2) {
        for (int i = 0; i < 16; i++) {
            if (fabs(m[i] - m2.m[i]) > 0.0000001)
                return false;
        }
        return true;
    }    
    static mat4_t & multiply(mat4_t &left, mat4_t &right) {
        static mat4_t m;
        m.m[0]  = left.m[0] * right.m[0]  + left.m[4] * right.m[1]  + left.m[8] * right.m[2]   + left.m[12] * right.m[3];
        m.m[4]  = left.m[0] * right.m[4]  + left.m[4] * right.m[5]  + left.m[8] * right.m[6]   + left.m[12] * right.m[7];
        m.m[8]  = left.m[0] * right.m[8]  + left.m[4] * right.m[9]  + left.m[8] * right.m[10]  + left.m[12] * right.m[11];
        m.m[12] = left.m[0] * right.m[12] + left.m[4] * right.m[13] + left.m[8] * right.m[14]  + left.m[12] * right.m[15];
        
        m.m[1]  = left.m[1] * right.m[0]  + left.m[5] * right.m[1]  + left.m[9] * right.m[2]   + left.m[13] * right.m[3];
        m.m[5]  = left.m[1] * right.m[4]  + left.m[5] * right.m[5]  + left.m[9] * right.m[6]   + left.m[13] * right.m[7];
        m.m[9]  = left.m[1] * right.m[8]  + left.m[5] * right.m[9]  + left.m[9] * right.m[10]  + left.m[13] * right.m[11];
        m.m[13] = left.m[1] * right.m[12] + left.m[5] * right.m[13] + left.m[9] * right.m[14]  + left.m[13] * right.m[15];
        
        m.m[2]  = left.m[2] * right.m[0]  + left.m[6] * right.m[1]  + left.m[10] * right.m[2]  + left.m[14] * right.m[3];
        m.m[6]  = left.m[2] * right.m[4]  + left.m[6] * right.m[5]  + left.m[10] * right.m[6]  + left.m[14] * right.m[7];
        m.m[10] = left.m[2] * right.m[8]  + left.m[6] * right.m[9]  + left.m[10] * right.m[10] + left.m[14] * right.m[11];
        m.m[14] = left.m[2] * right.m[12] + left.m[6] * right.m[13] + left.m[10] * right.m[14] + left.m[14] * right.m[15];
        
        m.m[3]  = left.m[3] * right.m[0]  + left.m[7] * right.m[1]  + left.m[11] * right.m[2]  + left.m[15] * right.m[3];
        m.m[7]  = left.m[3] * right.m[4]  + left.m[7] * right.m[5]  + left.m[11] * right.m[6]  + left.m[15] * right.m[7];
        m.m[11] = left.m[3] * right.m[8]  + left.m[7] * right.m[9]  + left.m[11] * right.m[10] + left.m[15] * right.m[11];
        m.m[15] = left.m[3] * right.m[12] + left.m[7] * right.m[13] + left.m[11] * right.m[14] + left.m[15] * right.m[15];

        return m;
    }
    void operator *= (mat4_t &mm) {
        
    }
    void getMatrix3(mat3_t<T> &m3) {
        m3.m00 = m00;
        m3.m01 = m01;
        m3.m02 = m02;
        m3.m10 = m10;
        m3.m11 = m11;
        m3.m12 = m12;
        m3.m20 = m20;
        m3.m21 = m21;
        m3.m22 = m22;
    }
    void makeIdentity() {
        memset(m, 0, sizeof(m));
        m00 = m11 = m22 = m33 = 1;
    }
    
    void makePerspertive(T fovyRadians, T aspect, T nearZ, T farZ) {
        T cotan = T(1.0f / tanf(fovyRadians / 2.0f));
        m00 = cotan / aspect; m01 = m02 = m03 = 0.0f;
        m10 = 0.0f; m11 = cotan; m12 = m13 = 0.0f;
        m20 = m21 = 0.0f; m22 = (farZ + nearZ) / (nearZ - farZ); m23 = -1.0f;
        m30 = m31 = 0.0f; m32 = (2.0f * farZ * nearZ) / (nearZ - farZ); m33 = 0.0f;
    }

    void makeTranslation(T x, T y, T z) {
        makeIdentity();
        m30 = x; m31 = y; m32 = z;
    }
    
    void makeRotation(T radians, T x, T y, T z) {
        vec3_t<T> v(x, y, z);
        v.normalize();
        float cos = cosf(radians);
        float cosp = 1.0f - cos;
        float sin = sinf(radians);
        
        m[0] = cos + cosp * v.x * v.x;
        m[1] = cosp * v.x * v.y + v.z * sin;
        m[2] = cosp * v.x * v.z - v.y * sin;
        m[3] = 0.0f;
        m[4] = cosp * v.x * v.y - v.z * sin;
        m[5] = cos + cosp * v.y * v.y;
        m[6] = cosp * v.y * v.z + v.x * sin;
        m[7] = 0.0f;
        m[8] = cosp * v.x * v.z + v.y * sin;
        m[9] = cosp * v.y * v.z - v.x * sin;
        m[10]= cos + cosp * v.z * v.z;
        m[11] = m[12] = m[13] = m[14] = 0.0f;
        m[15] = 1.0f;
    }
    
    void makeLookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ) {
        vec3_t<T> ev(eyeX, eyeY, eyeZ);
        vec3_t<T> cv(centerX, centerY, centerZ);
        vec3_t<T> uv(upX, upY, upZ);
        vec3_t<T> n = ev - cv;
        n.normalize();
        vec3_t<T> u = uv ^ n;
        u.normalize();
        vec3_t<T> v = n ^ u;
        
        m[0] = u.x;
        m[1] = v.x;
        m[2] = n.x;
        m[3] = 0.0f;
        m[4] = u.y;
        m[5] = v.y;
        m[6] = n.y;
        m[7] = 0.0f;
        m[8] = u.z;
        m[9] = v.z;
        m[10] = n.z;
        m[11] = 0.0f;
        m[12] = - u * ev;
        m[13] = - v * ev;
        m[14] = - n * ev;
        m[15] = 1.0f;
    }
};

typedef mat4_t<float> mat4f;
typedef mat4_t<double> mat4d;

    
    
}

#endif
