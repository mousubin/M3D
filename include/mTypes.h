//
//  mtypes.h
//  
//
//  Created by msb on 14-10-4.
//
//

#ifndef _mtypes_h
#define _mtypes_h

#include <stddef.h>

namespace mco {
    
    template<class T>
    class SingletonAutoRelease
    {
        T *_obj;
    public:
        SingletonAutoRelease(T *obj) {
            _obj = obj;
        }
        ~SingletonAutoRelease() {
            if (_obj->getInstance())
                delete _obj->getInstance();
        }
    };
};

#endif
