#pragma once

#include "../pch.h"

namespace JAF {

    struct TexturedVertex
    {
        GLfloat x,y,z, u,v;
    };

    struct PositionVertex {
        GLfloat x,y,z;
    };

    struct ParticleInstance {
        GLfloat x,y,z,radius,r,g,b,a;
    };
}