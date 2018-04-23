#pragma once

#include "../jawe/updater.h"
#include "vertex.h"
#include "../jawe/mesh.h"
#include "../jawe/bank.h"
#include "../jawe/instance_collector.h"
#include "director.h"

#include <random>

namespace JAF {

    class Updater : public JAWE::Updater
    {
    private:

        typedef std::vector<ParticleInstance> instance_vec;
        typedef JAWE::InstancedMesh<PositionVertex, ParticleInstance> particle_mesh;
        typedef std::shared_ptr<Particle> particle_ptr;
        typedef std::vector<particle_ptr> particle_vec;
        typedef std::shared_ptr<Math::Matrix> matrix_ptr;


        std::mt19937 m_generator { 840331 };
		Director m_director;

        JAWE::Bank<Particle> m_particleBank { [](){return new Particle(); } };

        std::mutex m_particleMutex;
        instance_vec m_particlesInstances;

        InstanceCollector<ParticleInstance> m_particleCollector;

        particle_vec m_particles;
        particle_vec m_particlesToAdd;

    protected:

        virtual void advance(float dt) override;

    public:

        virtual bool init() override;

        virtual ~Updater() {}

        void updateInstances(particle_mesh& mesh);

		void fireParticle(ParticleListener* pListener, const Behaviour* pBehaviour,
                          matrix_ptr pOffset, int type = 0, const Math::Vector3& factors = {1,1,1});
    };
}