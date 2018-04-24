#pragma once

#include "../pch.h"

namespace JAF {

    struct PositionVertex {
        GLfloat x,y,z;
    };

    struct ParticleInstance {
        GLfloat x,y,z,radius,r,g,b,a;
    };
}