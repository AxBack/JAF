#pragma once

#include "../pch.h"

namespace JAF {

    struct PositionVertex {
        GLfloat x,y,z;
    };

    struct ParticleInstance {
        GLfloat x,y,z,size,r,g,b,a;
    };
}