#pragma once

#include <fstream>
#include <sstream>
#include <android/asset_manager.h>

namespace JAWE { namespace IO {

    class TextFileReader
    {
    private:

        AAsset* m_pAsset;

    public:

        TextFileReader(AAssetManager* pAssetManager, const char* file)
            :m_pAsset(AAssetManager_open(pAssetManager, file, AASSET_MODE_STREAMING))
        {
        }

        virtual ~TextFileReader()
        {
            AAsset_close(m_pAsset);
        }

        std::string next()
        {
            std::string r;
            char c;
            int v = 0;
            while( (v = AAsset_read(m_pAsset, &c, 1)) > 0
                    && c != ':' && c != '\n')
            {
                r += c;
            }

            return r;
        }

        bool eof() { return m_pAsset == nullptr || AAsset_getRemainingLength(m_pAsset) == 0; }

        template <typename T> T read()
        {
            T item;
            return item.read(this);
        }
    };

    template <>
    std::string TextFileReader::read<std::string>()
    {
        return next();
    }

    template <>
    char TextFileReader::read<char>()
    {
        std::string item = next();
        return item[0];
    }

    template <>
    int TextFileReader::read<int>()
    {
        std::string item = next();
        return atoi(item.c_str());
    }

    template <>
    unsigned int TextFileReader::read<unsigned int>()
    {
        std::string item = next();
        return static_cast<unsigned int>(atoi(item.c_str()));
    }

    template <>
    float TextFileReader::read<float>()
    {
        std::string item = next();
        return static_cast<float>(atof(item.c_str()));
    }
}}