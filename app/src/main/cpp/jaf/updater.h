#pragma once

#include "../jawe/updater.h"
#include "vertex.h"
#include "../jawe/gfx/mesh.h"
#include "../jawe/bank.h"
#include "../jawe/gfx/instance_collector.h"
#include "director.h"

#include <random>

namespace JAF {

    class Updater : public JAWE::Updater
    {
    private:

        typedef std::vector<ParticleInstance> instance_vec;
        typedef JAWE::GFX::InstancedMesh<PositionVertex, ParticleInstance> particle_mesh;
        typedef std::vector<Particle*> particle_vec;

        std::mt19937 m_generator { 840331 };
		Director m_director;

        JAWE::Bank<Particle*> m_particleBank { [](){return new Particle();}, [](Particle* p) { delete p; } };

        std::mutex m_particleMutex;
        instance_vec m_particlesInstances;

        JAWE::GFX::InstanceCollector<ParticleInstance> m_particleCollector;

        particle_vec m_particles;
        particle_vec m_particlesToAdd;

    protected:

        virtual void advance(float dt) override;

    public:

        virtual bool init() override;

        virtual ~Updater()
		{}

        void updateInstances(particle_mesh& mesh);

		Particle* fireParticle();
    };
}