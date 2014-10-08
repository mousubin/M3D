//
//  TexturePVR.cpp
//  MRender
//
//  Created by msb on 14-10-7.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#include "Render/Texture.h"

namespace mrd {
    
    struct PVRHeader
    {
        uint32_t    header_length;
        uint32_t    height;
        uint32_t    width;
        uint32_t    mipmap_count;
        uint32_t    flags;
        uint32_t    data_length;
        uint32_t    bpp;
        uint32_t    bitmask_red;
        uint32_t    bitmask_green;
        uint32_t    bitmask_blue;
        uint32_t    bitmask_alpha;
        uint32_t    pvr_tag;
        uint32_t    surface_count;
    };

    enum {
        kBGRA8888 = 26,
        kPVRTC2 = 24,
        kPVRTC4 = 25
    };
    
#ifndef __MRENDER_IOS__
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG                      0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG                      0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG                     0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG                     0x8C03
#endif
    
    Texture2D *loadTexture2D_PVR(const char *buf, int bufSize) {
        
        Texture2D *tex = 0;
        PVRHeader *head = (PVRHeader *)buf;
        unsigned int flags = head->flags;
        unsigned int format = flags & 0xff;
        void *data = (char *)buf + sizeof(PVRHeader);
        tex = new Texture2D;
        if (format == kBGRA8888) {
            tex->setData(head->width, head->height, data);
        }
        else if (format == kPVRTC2) {
            tex->compressImage(head->width, head->height,
                GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, bufSize - sizeof(PVRHeader), data);
        }
        else if (format == kPVRTC4) {
            tex->compressImage(head->width, head->height,
                GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, bufSize - sizeof(PVRHeader), data);
        }
        return tex;
    }
    
};

