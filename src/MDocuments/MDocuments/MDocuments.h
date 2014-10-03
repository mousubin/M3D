//
//  MDocuments.h
//  MDocuments
//
//  Created by msb on 14-10-3.
//  Copyright (c) 2014年 msb. All rights reserved.
//


#include <string>
namespace mdoc {
  
    class MDocs
    {
        std::string _pathName;
    public:
        MDocs();
        virtual const char *findPathName(const char *pathName, const char *fileName) = 0;
    };
    
};