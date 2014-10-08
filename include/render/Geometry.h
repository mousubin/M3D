//
//  Geometry.h
//  
//
//  Created by msb on 14-9-30.
//
//

#ifndef _Geometry_h
#define _Geometry_h

#include "RenderTypes.h"
#include "Vertex.h"
#include "Shader.h"

namespace mrd {
    
    class Render;
    
    class Geometry : public RenderObject
    {
    protected:
        VertexBuffer _vb;
        Shader *_shader;
    public:
        virtual void render(Render *rd);
    };
    
    class Lines : public Geometry
    {
        
    public:
        Lines(ColorVertex *v, int nLines) {
            createLines(v, nLines);
        }
        void createLines(ColorVertex *v, int nLines) {
            _vb.setData(v, nLines * sizeof(ColorVertex), VA_VERTEX | VA_COLOR);
            _shader = Shader::getShader(0);
            
        }
    };

    
    
}

#endif
