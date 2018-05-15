#include "texture_loader.h"
#include "com_ptr.h"

#include <png.h>

namespace JAWE {

    bool isPow(int n) { return (n & (n-1)) == 0; }

    static ComPtr<AAsset*> s_asset  { [](AAsset* p) { AAsset_close(p); } };;

    void assetRead(png_structp png_ptr, png_bytep data, png_size_t length) {
        AAsset_read(s_asset.get(), data, length);
    }

    bool TextureLoader::load(AAssetManager* pAssetManager, const char* file, Texture& out) const
    {
        s_asset.set(AAssetManager_open(pAssetManager, file, AASSET_MODE_STREAMING));
        if(!s_asset.get())
            return false;

        png_byte header[8] {0};
        AAsset_read(s_asset.get(), header, 8);

        if(png_sig_cmp(header, 0, 8) != 0)
            return false;

        png_infop pInfo {nullptr}, pEnd {nullptr};

        ComPtr<png_structp> pPng(png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr),
                                 [&](png_structp p) { png_destroy_read_struct(&p, &pInfo, &pEnd); });
        if(!pPng.get())
            return false;

        pInfo = png_create_info_struct(pPng.get());
        if(!pInfo)
            return false;

        pEnd = png_create_info_struct(pPng.get());
        if(!pEnd)
            return false;

        if(setjmp(png_jmpbuf(pPng.get())))
            return false;

        png_set_read_fn(pPng.get(), nullptr, assetRead);

        png_set_sig_bytes(pPng.get(), 8);
        png_read_info(pPng.get(), pInfo);

        int bit_depth, color_type;
        png_uint_32 width, height;

        png_get_IHDR(pPng.get(), pInfo, &width, &height, &bit_depth, &color_type, nullptr, nullptr, nullptr);

        if(isPow((int)width) || isPow((int)height))
        {
            LOGE("Can only load pow2 images for now");
            return false;
        }

        png_read_update_info(pPng.get(), pInfo);

        size_t bytesPerRow = png_get_rowbytes(pPng.get(), pInfo);
        std::unique_ptr<png_byte[]> pImageData(new png_byte[bytesPerRow * height]);

        std::unique_ptr<png_bytep[]> pRowPointers(new png_bytep[height]);

        for(int i=0; i < height; ++i)
        {
            pRowPointers[i] = pImageData.get() + i * bytesPerRow;
        }

        png_read_image(pPng.get(), pRowPointers.get());

        return out.init(GL_RGBA, width, height, static_cast<const unsigned char*>(pImageData.get()));
    }

}