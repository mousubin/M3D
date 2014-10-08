//
//  Shader.cpp
//  MRender
//
//  Created by msb on 14-10-4.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#include "Shader.h"
#include <string.h>



namespace mrd {
    
    
    // 获取系统内部预定义的渲染器
    Shader *Shader::getShader(int type) {
        return ShaderFactory::getInstance()->getShader(0);
    }
    
    void Shader::setSource(const char *vs[], const char *ps[]) {
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
        
        make();
        bindAttrib();
        findUniform();
    }

    bool Shader::make() {
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
    
    void Shader::bindAttrib() {
        glGetProgramiv(_idPG, GL_ACTIVE_ATTRIBUTES, &_nAttribs);
        for (int i = 0; i < _nAttribs; i++) {
            char name[32];
            int len, size;
            GLenum type;
            glGetActiveAttrib(_idPG, i, 32, &len, &size, &type, name);
            int j = 0;
            for (j = 0; j < __vaConfigCount; j++) {
                if (strcmp(name, __vaConfig[j].name) == 0) {
                    _attribs[i] = j;
                    _attribBits |= __vaConfig[j].attrib;
                    break;
                }
            }
            if (j == __vaConfigCount) {
                AttribItem item;
                item.name = name;
                item.index = i;
                _UserAttribs.push_back(item);
                _attribs[i] = -1;
            }
        }
        
        int k = 0;
        for (int i=0; i<_nAttribs; i++){
            int j = _attribs[i];
            if (j >= 0)
                glBindAttribLocation(_idPG, i, __vaConfig[j].name);
            else
                glBindAttribLocation(_idPG, i, _UserAttribs[k++].name.c_str());
        }
    }
    
    void Shader::findUniform() {
        glGetProgramiv(_idPG, GL_ACTIVE_UNIFORMS, &_nUniforms);
        int k = 0;
        for (int i = 0; i < _nUniforms; i++) {
            char name[32];
            int len, size;
            GLenum type;
            glGetActiveUniform(_idPG, i, 32, &len, &size, &type, name);
            int loc = getUniform(name);
            int j = 0;
            for (j = 0; j < __standardUniformCount; j++) {
                if (strcmp(name, __standardUniform[j].name) == 0) {
                    _uniforms[k] = j;
                    _uniformLocations[k] = loc;
                    k++;
                    break;
                }
            }
            if (j == __standardUniformCount) {
                UniformItem item;
                item.name = name;
                item.index = i;
                _UserUniforms.push_back(item);
            }
        }
        
    }
    
//// ShaderFactory
    
    void ShaderFactory::init() {
        _shader.setSource((const char **)VS_COLOR, (const char **)PS_COLOR);
    }

};