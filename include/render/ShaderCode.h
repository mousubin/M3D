//
//  ShaderCode.h
//  
//
//  Created by msb on 14-9-19.
//
//

#ifndef _ShaderCode_h
#define _ShaderCode_h

#ifdef __MRENDER_IOS__
#define ES_PS   "#ifdef GL_FRAGMENT_PRECISION_HIGH\nprecision highp float;\n#else\nprecision mediump float;\n#endif\n"
#else
#define ES_PS
#endif


namespace mrd {
    
    typedef const char *ShaderStringType;
    
    const ShaderStringType VS_COLOR[] = {
        "attribute vec4 a_v;" \
        "attribute vec4 a_color;"\
        "varying vec4 v_color;"\
        "void main() {"\
        "   gl_Position = a_v;"\
        "   v_color = a_color;"\
        "}"
    };
    
    const ShaderStringType PS_COLOR[] = {
        ES_PS\
        "varying vec4 v_color;"\
        "void main() {"\
        "   gl_FragColor = v_color;"\
        "}"
    };
    
    const ShaderStringType VS_CODE[] = {
        "attribute vec4 a_v;" \
        "void main() {"\
        "   gl_Position = a_v;"\
        "}"
    };
    
    const ShaderStringType PS_CODE[] = {
        "void main() {"\
        "   gl_FragColor = vec4(1, 0, 0, 1);"\
        "}"
    };
};


#endif
