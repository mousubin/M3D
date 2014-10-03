//
//  MDocuments.m
//  MDocuments
//
//  Created by msb on 14-10-3.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "MDocuments.h"

namespace mdoc {


    MDocs::MDocs() {
        
    }
    
    const char * MDocs::findPathName(const char *pathName, const char *fileName) {
        
        NSString *filename = [[NSBundle mainBundle] pathForResource:@"A" ofType:@"txt"];
        _pathName = [filename cStringUsingEncoding:NSASCIIStringEncoding];
        return _pathName.c_str();
    }
    
    
}