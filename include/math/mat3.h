//
//  mat3.h
//  
//
//  Created by msb on 14-10-2.
//
//

#ifndef _mat3_h
#define _mat3_h


#include <math.h>

namespace mco {
    
    
    template<class T>
    union mat3_t
    {
        struct
        {
            T m00, m01, m02;
            T m10, m11, m12;
            T m20, m21, m22;
        };
        T m[9];
        
        operator const T *() { return m; };
        
        void makeIdentity() {
            memset(m, 0, sizeof(m));
            m00 = m11 = m22 = 1;
        }
        
        void invertAndTranspose() {
//            T v;
//            v = m01;
//            m01 = m10;
//            m10 = v;
//            v = m02;
//            m02 = m20;
//            m20 = v;
//            v = m12;
//            m12 = m21;
//            m21 = v;
        }
    };
    
    typedef mat3_t<float>   mat3f; 
}



#endif
