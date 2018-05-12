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
		m_deviation.push(true);

		m_releaseRotation.push( createRelease({0,0,0}, {0,1}, 0, nullptr));

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

		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {0,1080,0}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {0,-1080,0}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {0,0,1080}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {0,0,-1080}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {1080,0,0}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {-1080,0,0}}));

		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {0,2160,0}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {0,-2160,0}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {0,0,2160}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {0,0,-2160}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {2160,0,0}}));
		m_rotations.push_back(createPath(2, (Math::Vector3[]){{0,0,0}, {-2160,0,0}}));

		Math::Matrix front = Math::Matrix::setRotate(90,0,0);
		Math::Matrix back = Math::Matrix::setRotate(-90,0,0);
		Math::Matrix left = Math::Matrix::setRotate(0,0,90);
		Math::Matrix right = Math::Matrix::setRotate(0,0,-90);

		m_offsets.push({{8, (int[]){0,1,4,5,6,7,8,9}}, {front}});
		m_offsets.push({{8, (int[]){0,1,4,5,6,7,8,9}}, {back}});
		m_offsets.push({{8, (int[]){0,1,2,3,6,7,10,11}}, {left}});
		m_offsets.push({{8, (int[]){0,1,2,3,6,7,10,11}}, {right}});
		m_offsets.push({{8, (int[]){0,1,4,5,6,7,8,9}}, {front, back}});
		m_offsets.push({{8, (int[]){0,1,2,3,6,7,10,11}}, {left, right}});
	}

	SlowBurstBehaviour* SlowBurstCreator::create()
	{
		m_particleCreator.step();
		SlowBurstBehaviour* p = getBehaviour();
		p->init(rand(m_timeRange));

		Offsets* pOffset = m_offsets.frontPtr();
		p->add(m_nrParticlesPerBurst.front(),
			   rand(m_intervalRange),
			   m_rotations[pOffset->rotations.front()].get(),
			   m_particleCreator.create(),
			   pOffset->transforms.size(),
			   &pOffset->transforms[0]);

		return p;
	}
}
