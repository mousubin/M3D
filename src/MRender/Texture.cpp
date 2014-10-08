//
//  Texture.cpp
//  MRender
//
//  Created by msb on 14-10-7.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#include "Texture.h"
#include "mTypes.h"

#include <string.h>
#include "TextureDDS.cpp"
#include "TexturePVR.cpp"


namespace mrd {
    
    Texture2D *TextureFactory::loadTexture2D(const char *buf, int bufSize) {
        PVRHeader *pvr = (PVRHeader *)buf;
        if (strncmp(buf, "DDS ", 4) == 0) {
            return loadTexture2D_DDS(buf, bufSize);
        }
        else if (strncmp((char *)(&pvr->pvr_tag), "PVR!", 4) == 0)
        {
            return loadTexture2D_PVR(buf, bufSize);
        }
        return 0;
    }
}


