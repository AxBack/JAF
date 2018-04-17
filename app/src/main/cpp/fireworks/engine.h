#pragma once

#include "../jawe/engine.h"

namespace Fireworks {

    class Engine : public JAWE::Engine
    {
    private:

    public:

        Engine()
            : JAWE::Engine()
        {
        }

        virtual ~Engine()
        {
        }

        virtual bool init(AAssetManager *pAssetManager) override;

        virtual bool render() override;

        virtual void resume() override { }

        virtual void pause() override { }

    };

}