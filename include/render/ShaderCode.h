//
//  ShaderCode.h
//  
//
//  Created by msb on 14-9-19.
//
//

#ifndef _ShaderCode_h
#define _ShaderCode_h


#define SHADER_VERSION  "#ifdef GL_ES\n #ifdef GL_FRAGMENT_PRECISION_HIGH\nprecision highp float;\n#else\nprecision mediump float;\n#endif\n#endif\n"


namespace mrd {
    
    typedef const char *ShaderStringType;
    
    const ShaderStringType VS_CODE[] = {
        "attribute vec4 a_v;" \
        "void main() {"\
        "   gl_Position = a_v;"\
        "}"
    };
    
    const ShaderStringType PS_CODE[] = {
        SHADER_VERSION\
        "void main() {"\
        "   gl_FragColor = vec4(1, 0, 0, 1);"\
        "}"
    };
   
    const ShaderStringType VS_COLOR[] = {
        "uniform mat4 u_mvp;"\
        "attribute vec4 a_v;" \
        "attribute vec4 a_color;"\
        "varying vec4 v_color;"\
        "void main() {"\
        "   gl_Position = u_mvp * a_v;"\
        "   v_color = a_color;"\
        "}"
    };
    
    const ShaderStringType PS_COLOR[] = {
        SHADER_VERSION\
        "varying vec4 v_color;"\
        "void main() {"\
        "   gl_FragColor = v_color;"\
        "}"
    };
    
    const ShaderStringType VS_MESH[] = {
        "uniform mat4 u_mvp;"\
        "uniform mat3 u_mNormal;"\
        "attribute vec4 a_v;" \
        "attribute vec3 a_vn;"\
        "varying vec4 v_color;"\
        "void main() {"\
        "   vec3 lightPos = vec3(1.0, 1.0, 1.0);"\
        "   vec3 lightDir = normalize(lightPos - a_v.xyz);"\
        "   v_color = vec4(0.3, 0.3, 0.3, 1.0) + vec4(0.6, 0.6, 0.0, 1.0) * dot(normalize(u_mNormal * a_vn), lightPos);"\
        "   v_color.w = 1.0;"\
        "   gl_Position = u_mvp * a_v;"\
        "}"
    };
    //
    const ShaderStringType PS_MESH[] = {
        SHADER_VERSION\
        "varying vec4 v_color;"\
        "void main() {"\
        "   gl_FragColor = v_color;"\
        "}"
    };
    
    const ShaderStringType VS_UI[] = {
        "attribute vec4 a_v;" \
        "attribute vec2 a_tex0;" \
        "varying vec2 v_tex0;"\
        "void main() {"\
        "   gl_Position = a_v;"\
        "   v_tex0 = a_tex0;"\
        "}"
    };
    
    const ShaderStringType PS_UI[] = {
        SHADER_VERSION\
        "uniform sampler2D u_tex0;"\
        "varying vec2 v_tex0;"\
        "void main() {"\
        "   vec4 c; "\
        "   c.xy = v_tex0;"\
        "   gl_FragColor = texture2D(u_tex0, v_tex0);;"\
        "}"
    };
};
//

#endif
