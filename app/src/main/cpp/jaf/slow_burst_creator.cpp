#include "slow_burst_creator.h"

namespace JAF {

	void SlowBurstCreator::ParticleCreator::init()
	{
		m_gravity.push({0,0,0}, 0.2f);
		m_gravity.push({0,-50,0});
		m_gravity.push({0,-100,0});

		m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {0,1000,0}}));
		m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {0,300,0}}));
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {0,300,0}, {0,300,0}}));
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {0,500,0}, {0,500,0}}));

		m_sizes.push(createPath(4, (float[]){5,4,2,0} ));
		m_sizes.push(createPath(4, (float[]){6,8,6,0}));
		m_sizes.push(createPath(4, (float[]){4,1,1,0}));
		m_sizes.push(createPath(4, (float[]){2,8,8,0}));
		m_sizes.push(createPath(4, (float[]){15,9,6,0}));

		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,1,1,1}, {0,0,0,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,0,0,1}, {1,0,0,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,1,0,1}, {0,1,0,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,0,1,1}, {0,0,1,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,1,0,1}, {1,1,0,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {0,1,1,1}, {0,1,1,0}}));
		m_colors.push(createPath(3, (Color[]){{1,1,1,1}, {1,0,1,1}, {1,0,1,0}}));

		m_deviation.push(false);

		m_releaseRotation.push( createRelease({0,0,0}, {0,1}, 0, nullptr));

		m_timeDeviation.push(0.0f);
		m_positionDeviation.push(0.0f);
		m_sizeDeviation.push(0.0f);
		m_colorDeviation.push(0.0f);
	}

	SlowBurstCreator::SlowBurstCreator()
		: PathBehaviourCreator(5)
	{
		m_particleCreator.init();
	}

	SlowBurstBehaviour* SlowBurstCreator::create()
	{
		m_particleCreator.step();
		SlowBurstBehaviour* p = getBehaviour();
		p->init(rand(m_timeRange));

		p->add(1, 0.5f, m_particleCreator.create());

		return p;
	}
}
