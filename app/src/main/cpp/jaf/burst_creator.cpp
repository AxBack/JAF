#include "burst_creator.h"
#include "settings.h"

namespace JAF {

	BurstCreator::BurstCreator()
		: PathBehaviourCreator(5)
	{
	}

	void BurstCreator::init()
	{
		m_gravity.push({0,0,0}, 0.2f);
		m_gravity.push({0,-50,0});
		m_gravity.push({0,-100,0});

		m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {0,1000,0}}), 1.25f);
		m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {0,300,0}}), 1.25f);
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {0,500,0}, {0,500,0}}));
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {0,250,0}, {0,300,0}}));
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {0,450,0}, {0,500,0}}));
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {0,500,0}, {0,500,0}}));
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {0,400,100}, {0,500,200}}), 2);
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {0,400,-100}, {0,500,-200}}), 2);
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {100,400,0}, {200,500,0}}), 2);
		m_positions.push(createPath(3, (Vector3[]){{0,0,0}, {-100,400,0}, {-200,500,0}}), 2);

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

		m_deviation.push(true, 0.25f);
		m_deviation.push(false);

		m_releaseRotation.push( createRelease({180,180,180}, {0,1}, 0, nullptr));
		m_releaseRotation.push( createRelease({90,360,90}, {1.5f, 2.0f}, 1, (Math::Vector3[]){{0,0,0}}));
		m_releaseRotation.push( createRelease({45,360,45}, {1.5f, 2.0f}, 1, (Math::Vector3[]){{0,0,0}}));
		m_releaseRotation.push( createRelease({10,360,10}, {1.5f, 2.0f}, 1, (Math::Vector3[]){{0,0,0}}));

		for(float v=0.0f; v < 0.3f; v+=0.05f)
		{
			m_timeDeviation.push(v);
			m_positionDeviation.push(v);
			m_sizeDeviation.push(v);
			m_colorDeviation.push(v);
		}
	}

	BurstBehaviour* BurstCreator::create()
	{
		BurstBehaviour* p = getBehaviour();
		if(m_deviate)
		{
			p->init(rand(m_lifeRange), m_timeDeviation.front());
			p->setDeviation(m_positionDeviation.front(), m_sizeDeviation.front(),
							m_colorDeviation.front());
		}
		else
			p->init(rand(m_lifeRange));

		fill(p, rand(m_positionRange), &m_positions);
		fill(p, rand(m_sizeRange), &m_sizes);
		fill(p, rand(m_colorRange), &m_colors);

		p->setGravity(m_gravity.front());
		p->setReleaseRotation(m_pCurrentRelease->rot);
		if(m_pCurrentRelease->pForced)
			p->add(rand(m_pCurrentRelease->weight), m_pCurrentRelease->pForced.get());

		p->normalize();

		return p;
	}
}
