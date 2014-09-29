//
//  Shader.h
//  
//
//  Created by msb on 14-9-19.
//
//

#ifndef _Shader_h
#define _Shader_h

#include "math/math.h"
#include "ShaderCode.h"

namespace mrd {
    
    
    class Shader
    {
        const char *_vs, *_ps;
        int _idVS, _idPS, _idPG;
        int _retVS, _retPS, _retPG;
        char _log[256];
    public:
        Shader() {
            _idVS = 0; _idPS = 0; _idPG = 0;
            _retVS = 0; _retPS = 0; _retPG = 0;
            _log[0] = 0;
        }
        ~Shader() {
            if (_idPG)
                glDeleteProgram(_idPG);
        }
        operator unsigned int() { return _idPG; }
        void setSource(const char *vs[], const char *ps[]) {
            _idVS = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(_idVS, 1, vs, 0);
            glCompileShader(_idVS);
            glGetShaderiv(_idVS, GL_COMPILE_STATUS, &_retVS);
            if (!_retVS) {
                int n;
                glGetShaderInfoLog(_idVS, 256, &n, _log);
            }
            
            _idPS = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(_idPS, 1, ps, 0);
            glCompileShader(_idPS);
            glGetShaderiv(_idPS, GL_COMPILE_STATUS, &_retPS);
            if (!_retPS) {
                int n;
                glGetShaderInfoLog(_idPS, 256, &n, _log);
            }
            
            _idPG = glCreateProgram();
            glAttachShader(_idPG, _idVS);
            glAttachShader(_idPG, _idPS);
        }
        int getUniform(const char *name) {
            return glGetUniformLocation(_idPG, name);
        }
        void setUniform(unsigned int id, mco::mat4f &m) {
            glUniformMatrix4fv(id, 1, false, m);
        }
        void setTexture(unsigned int id, unsigned int tex) {
            glUniform1i(id, tex);
        }
        bool make() {
            if (!_idPG)
                return false;
            glLinkProgram(_idPG);
            glGetProgramiv(_idPG, GL_LINK_STATUS, &_retPG);
            if (!_retPG) {
                int n;
                glGetProgramInfoLog(_idPG, 256, &n, _log);
            }
            glValidateProgram(_idPG);
            glGetProgramiv(_idPG, GL_VALIDATE_STATUS, &_retPG);
            if (!_retPG) {
                int n;
                glGetProgramInfoLog(_idPG, 256, &n, _log);
            }
            
            if (_idVS) {
                glDetachShader(_idPG, _idVS);
                glDeleteShader(_idVS);
            }
            if (_idPS) {
                glDetachShader(_idPG, _idPS);
                glDeleteShader(_idPS);
            }
            return true;
        }
        void apply() {
            glUseProgram(_idPG);
        }
    };
};

#endif
