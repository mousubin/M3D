//
//  ViewController.h
//  MRenderTest_iOS
//
//  Created by msb on 14-9-17.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

#include "Render/Render.h"

@interface ViewController : GLKViewController

@property mrd::Render *rd;

@end
