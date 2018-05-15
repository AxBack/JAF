#pragma once

#include "texture.h"

namespace JAWE {

    class TextureLoader
    {
    private:

    public:

        bool load(AAssetManager* pAssetManager, const char* file, Texture& out) const;

    };
}