#include "slow_burst_creator.h"

namespace JAF {

	void SlowBurstCreator::ParticleCreator::init()
	{
		m_gravity.push({0,0,0}, 0.2f);
		m_gravity.push({0,-50,0});
		m_gravity.push({0,-100,0});

		m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {300,0,0}}));
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {300,0,0}, {300,0,0}}));
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {500,0,0}, {500,0,0}}));

		m_sizes.push(createPath(4, (float[]){15,4,2,0} ));
		m_sizes.push(createPath(4, (float[]){16,8,6,0}));
		m_sizes.push(createPath(4, (float[]){14,1,1,0}));
		m_sizes.push(createPath(4, (float[]){12,8,8,0}));
		m_sizes.push(createPath(4, (float[]){15,9,6,0}));

		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,1,1,1}, {0,0,0,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,0,0,1}, {1,0,0,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,1,0,1}, {0,1,0,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,0,1,1}, {0,0,1,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,1,0,1}, {1,1,0,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,1,1,1}, {0,1,1,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,0,1,1}, {1,0,1,0}}));

		m_deviation.push(false);
		m_deviation.push(true);

		m_releaseRotation.push( createRelease({0,0,0}, {0,1}, 0, nullptr));

		m_lifeRange = {0.8, 1.2};

		m_timeDeviation.push(0.0f);
		m_timeDeviation.push(0.25f);
		m_positionDeviation.push(0.0f);
		m_positionDeviation.push(0.25f);
		m_sizeDeviation.push(0.0f);
		m_sizeDeviation.push(0.25f);
		m_colorDeviation.push(0.0f);
		m_colorDeviation.push(0.25f);
	}

	SlowBurstCreator::SlowBurstCreator()
		: PathBehaviourCreator(5)
	{
		m_particleCreator.init();

		m_nrParticlesPerBurst.push(1);
		m_nrParticlesPerBurst.push(2);
		m_nrParticlesPerBurst.push(3);

		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,360,0}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,540,0}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,960,0}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,1080,0}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,-1080,0}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,1080,1080}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,-1080,-1080}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {1080,1080,0}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {-1080,-1080,0}}));

		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,2160,0}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,-2160,0}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,1080,2160}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {0,-1080,-2160}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {2160,1080,0}}));
		m_rotations.push(createPath(2, (JAWE::MATH::Vector3[]){{0,0,0}, {-2160,-1080,0}}));


		m_nrPerCircleStep.push(5);
		m_nrPerCircleStep.push(6);
		m_nrPerCircleStep.push(7);
		m_nrPerCircleStep.push(8);
		m_nrPerCircleStep.push(9);
		m_nrPerCircleStep.push(10);
	}

	SlowBurstBehaviour* SlowBurstCreator::create()
	{
		m_particleCreator.step();
		SlowBurstBehaviour* p = getBehaviour();
		p->init(rand(m_timeRange));

		p->add(m_nrParticlesPerBurst.front(),
			   rand(m_intervalRange),
			   m_rotations.front().get(),
			   m_particleCreator.create(),
			   m_nrPerCircleStep.front());

		return p;
	}
}
