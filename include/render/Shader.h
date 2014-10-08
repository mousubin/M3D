//
//  Shader.h
//  
//
//  Created by msb on 14-9-19.
//
//

#ifndef _Shader_h
#define _Shader_h

#include <string>
#include <vector>
#include "mTypes.h"
#include "RenderTypes.h"
#include "math/math.h"
#include "ShaderCode.h"


namespace mrd {
    
    
    class Shader
    {
        const char *_vs, *_ps;
        int _idVS, _idPS, _idPG;
        int _retVS, _retPS, _retPG;
    public:
        // 系统预定义VertexAttrib
        int _attribs[16];
        int _nAttribs;
        unsigned int _attribBits;
        // 用户自定义VertexAttrib
        struct AttribItem
        {
            std::string name;
            int index;
        };
        std::vector<AttribItem> _UserAttribs;
        // 系统预定义Uniform
        int _uniforms[16];
        int _uniformLocations[16];
        int _nUniforms;
        struct UniformItem
        {
            std::string name;
            int index;
        };
        // 用户自定义Uniform
        std::vector<UniformItem> _UserUniforms;
        char _log[256];
    public:
        Shader() {
            _idVS = 0; _idPS = 0; _idPG = 0;
            _retVS = 0; _retPS = 0; _retPG = 0;
            _log[0] = 0;
            _attribBits = 0;
        }
        ~Shader() {
            if (_idPG)
                glDeleteProgram(_idPG);
        }
        operator unsigned int() { return _idPG; }
        void setSource(const char *vs[], const char *ps[]);
        int getUniform(const char *name) {
            return glGetUniformLocation(_idPG, name);
        }
        void setUniform(unsigned int id, mco::mat4f &m) {
            glUniformMatrix4fv(id, 1, false, m);
        }
        void setUniform(unsigned int id, mco::mat3f &m) {
            glUniformMatrix3fv(id, 1, false, m);
        }
        void setTexture(unsigned int id, unsigned int tex) {
            glUniform1i(id, tex);
        }
        bool make();
        void bindAttrib();
        void findUniform();
        void apply() { glUseProgram(_idPG); }
        
        // 获取系统内部预定义的渲染器
        static Shader *getShader(int type);
        
    };
    
    class ShaderFactory
    {
        Shader _shader;
    public:
        static ShaderFactory *getInstance() {
            static ShaderFactory *sf = NULL;
            if (sf == NULL) {
                sf = new ShaderFactory;
                sf->init();
                static mco::SingletonAutoRelease<ShaderFactory> autoRelease(sf);
            }
            return sf;
        }
        void init();
        Shader *getShader(int type) {
            return &_shader;
        }
        
    };
    
};

#endif
