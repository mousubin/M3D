//
//  View.h
//  MRenderTest_OSX
//
//  Created by msb on 14-9-17.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "Render/Render.h"

@interface View : NSOpenGLView

@property mrd::Render *rd;


- (void) initRender;

@end
