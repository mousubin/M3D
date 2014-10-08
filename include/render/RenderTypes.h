//
//  RenderTypes.h
//  
//
//  Created by msb on 14-9-17.
//
//

#ifndef _RenderTypes_h
#define _RenderTypes_h

#ifdef __MRENDER_IOS__
	#include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>
#else
	#ifdef WIN32
		#include <GL/glew.h>
	#else
		#include <OpenGL/gl.h>
	#endif
#endif


#include <string>
#include "math/vec4.h"

namespace mrd {
    
    enum ClearBufferBit{
        ColorBufferBit = GL_COLOR_BUFFER_BIT,
        DepthBufferBit = GL_DEPTH_BUFFER_BIT,
    };
    
    typedef mco::vec4f   Color;
#ifndef WIN32
    typedef const char *    LPCTSTR;
#endif
    
    enum VertexAttribBit{
        VA_VERTEX = 1,
        VA_NORMAL = 2,
        VA_COLOR = 4,
        VA_TEX0 = 8
    };
    
    struct VertexAttrib
    {
        int attrib;
        int size;
        int type;
        bool normalized;
        int width;
        char name[32];
    };
    
    const VertexAttrib __vaConfig[] ={
        VA_VERTEX, 3, GL_FLOAT, false, 12, "a_v",
        VA_NORMAL, 3, GL_FLOAT, false, 12, "a_vn",
        VA_COLOR, 4, GL_UNSIGNED_BYTE, true, 4, "a_color",
        VA_TEX0, 2, GL_FLOAT, false, 8, "a_tex0",
    };
    const int __vaConfigCount = sizeof(__vaConfig) / sizeof(VertexAttrib);
    
    enum UniformBit
    {
        U_MVP = 1,
        U_NORMAL_MATRIX = 2,
        U_TIME = 4,
    };
    
    struct UniformInfo
    {
        int uniform;
        char name[32];
    };
    const UniformInfo __standardUniform[] = {
        U_MVP, "u_mvp",
        U_NORMAL_MATRIX, "u_mNormal",
        U_TIME, "u_time"
    };
    const int __standardUniformCount = sizeof(__standardUniform) / sizeof(UniformInfo);
    
    class Render;
    class RenderObject
    {
    public:
        virtual void render(Render *rd) = 0;
    };
};

#endif
