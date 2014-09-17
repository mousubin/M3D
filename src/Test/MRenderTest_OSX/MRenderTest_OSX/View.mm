//
//  View.m
//  MRenderTest_OSX
//
//  Created by msb on 14-9-17.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#import "View.h"

#include <OpenGL/gl.h>
#include "render/render.h"

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


@implementation View

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    OSXTargetFactory *tf = OSXTargetFactory::getInstance();
    tf->setContext(self.openGLContext);
    mrd::RenderSystem::getInstance()->installTargetFactory(tf);
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    
    mrd::Render render;
    render.beginScene();
    render.clear();
    render.endScene();
    render.show();
}

@end
