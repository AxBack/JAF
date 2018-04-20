#pragma once

#include "../jawe/updater.h"
#include "vertex.h"
#include "../jawe/mesh.h"
#include "particle.h"
#include "../jawe/bank.h"
#include "../jawe/instance_collector.h"

#include <random>

namespace JAF {

    class Updater : public JAWE::Updater, OnReleaseListener
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
        Behaviour m_rocketBehaviour;
		Behaviour m_explosionBeaviour;
        vec3_path position1;
        vec3_path position2;
		vec3_path position3;
		vec3_path position4;
        float_path size1;
        float_path size2;
        color_path color1;
        color_path color2;
        float m_counter;

        void fireParticle(const Behaviour* pBehaviour, const Math::Vector3& offset);

    protected:

        virtual void advance(float dt) override;

    public:

        Updater()
            : JAWE::Updater()
            , m_generator(840331)
            , m_counter(0)
			, m_particleBank([this](){return new Particle(this); })
        {}

        virtual bool init() override;

        virtual ~Updater() {}

        void updateInstances(particle_mesh& mesh);

		virtual void onRelease(int nr, const Math::Vector3& offset, const Behaviour* pBehaviour) override
		{
			for(UINT i=0; i<nr; ++i)
				fireParticle(pBehaviour, offset);
		}
    };
}