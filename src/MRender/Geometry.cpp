//
//  Geometry.cpp
//  MRender
//
//  Created by msb on 14-10-5.
//  Copyright (c) 2014年 msb. All rights reserved.
//

#include "Render/Geometry.h"
#include "Render/Render.h"

namespace mrd {
    
    void Geometry::render(Render *rd) {
        _shader->apply();
        rd->setUniform(*_shader);
        _vb.apply(_shader->_attribBits);
        rd->draw(GL_LINES, 0, _vb.getVertexCount());
    }


};
