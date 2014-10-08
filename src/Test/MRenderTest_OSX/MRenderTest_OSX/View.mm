//
//  View.m
//  MRenderTest_OSX
//
//  Created by msb on 14-9-17.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#import "View.h"

#include <OpenGL/gl.h>

#include "../../MRenderTestShare/T_Render.h"


class OSXTarget : public mrd::Target
{
    NSOpenGLContext *_context;
public:
    OSXTarget(NSOpenGLContext *context) {
        _context = context;
    }
    void active() {
        [_context makeCurrentContext];
    }
};

class OSXTargetFactory : public mrd::TargetFactory
{
    NSOpenGLContext *_context;
public:
    static OSXTargetFactory *getInstance(){
        static OSXTargetFactory *_tf = NULL;
        if (_tf == NULL) {
            _tf = new OSXTargetFactory;
        }
        return _tf;
    }
    void setContext(NSOpenGLContext *context) {
        _context = context;
    }
    virtual mrd::Target *createTarget() {
        return new OSXTarget(_context);
    }
};





CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now, const CVTimeStamp *outputTime,
                                      CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext);

CVReturn OutputCallback(CVDisplayLinkRef displayLink,
                                                const CVTimeStamp *inNow,
                                                const CVTimeStamp *outputTime,
                                                CVOptionFlags flagsIn,
                                                CVOptionFlags *flagsOut,
                                                void *displayLinkContext)
{
    CVReturn result = [(__bridge View*)displayLinkContext getFrameForTime:outputTime];
    return result;
}


@implementation View

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime
{
    // Add your drawing codes here
    [self display];
    return kCVReturnSuccess;
}

- (id)init
{
    return [super init];
}

- (void) reshape
{
    NSRect backingBounds = [self convertRectToBacking:[self bounds]];
    GLsizei backingPixelWidth  = (GLsizei)(backingBounds.size.width),
    backingPixelHeight = (GLsizei)(backingBounds.size.height);
    if (_rd)
        _rd->setViewport(0, 0, backingPixelWidth, backingPixelHeight);
}


- (void)initRender
{
    static bool bInit = false;
    if (bInit)
        return;
    bInit = true;
    
     OSXTargetFactory *tf = OSXTargetFactory::getInstance();
    tf->setContext(self.openGLContext);
    mrd::RenderSystem::getInstance()->installTargetFactory(tf);
    
    CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
    CVDisplayLinkSetOutputCallback(_displayLink, &OutputCallback, (__bridge void *)self);
    CVDisplayLinkStart(_displayLink);
    
    NSString *resPath = [[NSBundle mainBundle] resourcePath];
    std::string strResPath = [resPath cStringUsingEncoding:NSASCIIStringEncoding];
    strResPath += "/data";
    _archive.open(strResPath.c_str());
    
    _rd = new mrd::Render;
    _rd->init();
    std::cout << _rd->_openGLInfo;
    
    MT_CASES
    {
        MT_RENDER_CASE(Shape, _rd)
        MT_RENDER_CASE(Geometry, _rd)
        MT_RENDER_CASE(Tex, _rd)
        MT_RENDER_CASE(Vertex, _rd)
    }
    MRenderTestSuite::getInstance()->setRender(_rd);
}

- (void)drawRect:(NSRect)dirtyRect
{
    
    //[self  setWantsBestResolutionOpenGLSurface:YES];
    [[self openGLContext] makeCurrentContext];
    [super drawRect:dirtyRect];
    [self initRender];
    
    NSRect backingBounds = [self convertRectToBacking:[self bounds]];
    GLsizei backingPixelWidth  = (GLsizei)(backingBounds.size.width),
    backingPixelHeight = (GLsizei)(backingBounds.size.height);
    _rd->setViewport(0, 0, backingPixelWidth, backingPixelHeight);
    MT_RENDER_RUN
    
//    glColor3f(1.0f, 0.85f, 0.35f);
//    glBegin(GL_TRIANGLES);
//    {
//        glVertex3f(  0.0,  0.6, 0.0);
//        glVertex3f( -0.2, -0.3, 0.0);
//        glVertex3f(  0.2, -0.3 ,0.0);
//    }
//    glEnd();
//    glFlush();
}

@end
