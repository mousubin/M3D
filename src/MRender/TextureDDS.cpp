//
//  TextureDDS.cpp
//  MRender
//
//  Created by msb on 14-10-7.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#include "Texture.h"

using namespace mco;

namespace mrd {
    
    typedef unsigned int DWORD;
    typedef int LONG;
    typedef unsigned char BYTE;
    
#define MAKEFOURCC(ch0, ch1, ch2, ch3) ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) \
    | ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))
#define FOURCC_DXT1  (MAKEFOURCC('D','X','T','1'))
#define FOURCC_DXT2  (MAKEFOURCC('D','X','T','2'))
#define FOURCC_DXT3  (MAKEFOURCC('D','X','T','3'))
#define FOURCC_DXT4  (MAKEFOURCC('D','X','T','4'))
#define FOURCC_DXT5  (MAKEFOURCC('D','X','T','5'))
    
    typedef struct _DDCOLORKEY
    {
        unsigned int dwColorSpaceLowvalue;   // low boundary of color space that is to
        // be treated as Color Key, inclusive
        unsigned int dwColorSpaceHighvalue;  // high boundary of color space that is
        // to be treated as Color Key, inclusive
    } DDCOLORKEY;
    
    typedef struct _DDPIXELFORMAT {
        DWORD dwSize;
        DWORD dwFlags;
        DWORD dwFourCC;
        union
        {
            DWORD dwRGBBitCount;
            DWORD dwYUVBitCount;
            DWORD dwAlphaBitDepth;
        };
        union
        {
            DWORD dwRBitMask;
            DWORD dwYBitMask;
        };
        union
        {
            DWORD dwGBitMask;
            DWORD dwUBitMask;
        };
        union
        {
            DWORD dwBBitMask; 
            DWORD dwVBitMask; 
        }; 
        union 
        { 
            DWORD dwRGBAlphaBitMask; 
        }; 
    } DDPIXELFORMAT, * LPDDPIXELFORMAT;
    
    typedef struct _DDSCAPS2 {
        DWORD dwCaps;
        DWORD dwCaps2;
        DWORD dwCaps3;
        DWORD dwCaps4;
    } DDSCAPS2, * LPDDSCAPS2;
    
    typedef struct _DDSURFACEDESC2 {
        DWORD      dwSize;
        DWORD      dwFlags;
        DWORD      dwHeight;
        DWORD      dwWidth;
        union {
            LONG  lPitch;
            DWORD dwLinearSize;
        };
        union {
            DWORD dwBackBufferCount;
            DWORD dwDepth;
        };
        union {
            DWORD dwMipMapCount;
            DWORD dwRefreshRate;
            DWORD dwSrcVBHandle;
        };
        DWORD      dwAlphaBitDepth;
        DWORD      dwReserved;
        DWORD      lpSurface;
        union {
            DDCOLORKEY ddckCKDestOverlay;
            DWORD      dwEmptyFaceColor;
        };
        DDCOLORKEY ddckCKDestBlt;
        DDCOLORKEY ddckCKSrcOverlay;
        DDCOLORKEY ddckCKSrcBlt;
        union {
            DDPIXELFORMAT ddpfPixelFormat;
            DWORD         dwFVF;
        };
        DDSCAPS2   ddsCaps;
        DWORD      dwTextureStage;
    } DDSURFACEDESC2;
    

#ifdef __MRENDER_IOS__
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                      0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                     0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                     0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                     0x83F3
#endif
    
    Texture2D *TextureFactory::loadTexture2D_DDS(const char *buf, int bufSize) {
        if (strncmp(buf, "DDS ", 4) != 0) {
            return NULL;
        }
        int sz = sizeof(DDSURFACEDESC2);
        DDSURFACEDESC2 *ddsd = (DDSURFACEDESC2 *)(buf + 4);
        int format = 0;
        int factor = 0;
        switch (ddsd->ddpfPixelFormat.dwFourCC) {
            case FOURCC_DXT1:
                format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                factor = 2;
                break;
            case FOURCC_DXT3:
                format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                factor = 4;
                break;
            case FOURCC_DXT5:
                format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                factor = 4;
                break;
            default:
                return NULL;
                break;
        }
        
        if (ddsd->dwLinearSize == 0)
        {
            return NULL;
        }
        Texture2D *tex = new Texture2D;
        int size = 0;
        if (ddsd->dwMipMapCount > 1)
            size = ddsd->dwLinearSize * factor;
        else
            size = ddsd->dwLinearSize;
        tex->compressImage(ddsd->dwWidth, ddsd->dwHeight, format, size, (void *)(buf + 4 + ddsd->dwSize));
        return tex;
    }
    
    
}








