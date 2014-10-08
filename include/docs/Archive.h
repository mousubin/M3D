//
//  Archive.h
//  
//
//  Created by msb on 14-10-7.
//
//

#ifndef _Archive_h
#define _Archive_h

#include <string>
#include <stdio.h>

namespace mdoc {
    // 只读的档案文件库访问
    class Archive
    {
        std::string _rootPath;
    public:
        
        // 打开档案文件库
        bool open(const char *path) {
            _rootPath = path;
            return true;
        }
        // 打开文件，返回文件句柄
        long openFile(const char *path, const char *fileName) {
            std::string fullPath = _rootPath;
            if (path) {
                fullPath += "/";
                fullPath += path;
            }
            fullPath += "/";
            fullPath += fileName;
            FILE *fp = fopen(fullPath.c_str(), "rb");
            return (long)fp;
        }
        void closeFile(long idFile) {
            if (idFile == 0)
                return;
            FILE *fp = (FILE *)idFile;
            fclose(fp);
        }
        int getSize(long idFile) {
            if (idFile == 0)
                return 0;
            FILE *fp = (FILE *)idFile;
            fseek(fp, 0, SEEK_END);
            int size = (int)ftell(fp);
            fseek(fp, 0, SEEK_SET);
            return size;
        }
        // 读取文件内容，返回实际读取长度;buf为空时，返回文件长度
        int read(long idFile, void *buf, int bufSize) {
            FILE *fp = (FILE *)idFile;
            if (fp == NULL)
                return 0;
            fread(buf, 1, bufSize, fp);
            return 0;
        }
    };
};



#endif
