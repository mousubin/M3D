//
//  Shape.h
//  
//
//  Created by msb on 14-9-24.
//
//

#ifndef ____Shape__
#define ____Shape__

#include <stdio.h>
#include "Vertex.h"

namespace mrd {
    
    
    typedef VertexBuffer  Shape;
    
    class ShapeFactory
    {
    public:
        static Shape *createPyramid(float r = 1.0f) {
            MeshVertex v[] = {
                0.0f, 1.0f, 0.0f,   0.5774f, 0.5774, 0.5774,
                0.0f, 0.0f, 1.0f,   0.5774f, 0.5774, 0.5774,
                1.0f, 0.0f, 0.0f,   0.5774f, 0.5774, 0.5774,
                
                0.0f, 1.0f, 0.0f,   0.5774f, 0.5774, -0.5774,
                1.0f, 0.0f, 0.0f,   0.5774f, 0.5774, -0.5774,
                0.0f, 0.0f, -1.0f,   0.5774f, 0.5774, -0.5774,

                0.0f, 1.0f, 0.0f,   -0.5774f, 0.5774, -0.5774,
                0.0f, 0.0f, -1.0f,  -0.5774f, 0.5774, -0.5774,
                -1.0f, 0.0f, 0.0f,  -0.5774f, 0.5774, -0.5774,
                
                0.0f, 1.0f, 0.0f,   -0.5774f, 0.5774, 0.5774,
                -1.0f, 0.0f, 0.0f,  -0.5774f, 0.5774, 0.5774,
                0.0f, 0.0f, 1.0f,   -0.5774f, 0.5774, 0.5774,
                
                0.0f, 0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
                0.0f, 0.0f, -1.0f,  0.0f, -1.0f, 0.0f,
                1.0f, 0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
                
                0.0f, 0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
                -1.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
                0.0f, 0.0f, -1.0f,  0.0f, -1.0f, 0.0f,
            };
            Shape *s = new Shape;
            int n = sizeof(v) / sizeof(MeshVertex);
            for (int i = 0; i < n; i++) {
                v[i].x *= r;
                v[i].y *= r;
                v[i].z *= r;
            }
            s->setData(v, sizeof(v), VA_VERTEX | VA_NORMAL);
            return s;
        }
    
    };
    
};




#endif /* defined(____Shape__) */
