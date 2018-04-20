#pragma once

#include "../jawe/updater.h"
#include "vertex.h"
#include "../jawe/mesh.h"
#include "particle.h"
#include "../jawe/bank.h"

#include <random>

namespace JAF {

    class Updater : public JAWE::Updater
    {
    private:

        typedef JAWE::Path<Math::Vector3> vec3_path;
        typedef JAWE::Path<float> float_path;
        typedef JAWE::Path<Math::Color> color_path;
        typedef std::vector<ParticleInstance> instance_vec;
        typedef JAWE::InstancedMesh<PositionVertex, ParticleInstance> particle_mesh;
        typedef std::shared_ptr<Particle> particle_ptr;
        typedef std::vector<particle_ptr> particle_vec;


        std::mt19937 m_generator;

        JAWE::Bank<Particle> m_particleBank;

        std::mutex m_particleMutex;
        instance_vec m_particles;

        InstanceCollector<ParticleInstance> m_particleCollector;

        particle_vec m_items;
        particle_vec m_itemsToAdd;

        //temp
        Behaviour m_behaviour;
        vec3_path position1;
        vec3_path position2;
        float_path size1;
        float_path size2;
        color_path color1;
        color_path color2;

        void fireParticle(const Behaviour* pBehaviour);

    protected:

        virtual void advance(float dt) override;

    public:

        Updater()
            : JAWE::Updater()
            , m_generator(840331)
            , m_behaviour()
        {}

        virtual bool init() override;

        virtual ~Updater() {}

        void updateInstances(particle_mesh& mesh);
    };
}