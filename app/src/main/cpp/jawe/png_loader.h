#pragma once

#include <android/asset_manager.h>
#include <memory>

namespace JAWE {

    struct Png
    {
        const char* file;
        int width;
        int height;
        std::unique_ptr<unsigned char> pPixels;
    };

    class PngLoader
    {
    private:

        AAssetManager* m_pAssetManager { nullptr };

    public:

        PngLoader(AAssetManager* pAssetManager)
                : m_pAssetManager(pAssetManager)
        {}

        bool load(Png& data) const;

    };
}