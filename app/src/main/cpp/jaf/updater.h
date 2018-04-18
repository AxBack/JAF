#pragma once

#include "../jawe/updater.h"
#include "vertex.h"
#include "../jawe/mesh.h"
#include "particle.h"

#include <random>

namespace JAF {

    class Updater : public JAWE::Updater
    {
    private:

        typedef JAWE::Path<Math::Vector3> vec3_path;
        typedef JAWE::Path<float> float_path;
        typedef JAWE::Path<Math::Color> color_path;
        typedef std::vector<ParticleInstance> particle_vec;
        typedef JAWE::InstancedMesh<PositionVertex, ParticleInstance> particle_mesh;

        std::mt19937 m_generator;

        std::mutex m_particleMutex;
        particle_vec m_particles;

        InstanceCollector<ParticleInstance> m_particleCollector;

        std::vector<BehaviourInfluenced*> m_items;

        //temp
        Behaviour m_behaviour;
        vec3_path position;
        float_path size;
        color_path color;

    protected:

        virtual void advance(float dt) override;

    public:

        Updater()
            : JAWE::Updater()
            , m_generator(840331)
        {}

        virtual bool init() override;

        virtual ~Updater() {}

        void updateInstances(particle_mesh& mesh);
    };
}