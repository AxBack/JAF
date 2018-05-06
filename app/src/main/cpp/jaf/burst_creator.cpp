#include "burst_creator.h"
#include "settings.h"

namespace JAF {

	BurstCreator::BurstCreator()
		: PathBehaviourCreator(5)
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

		for(float v=0.0f; v < 0.6f; v+=0.1f)
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
		if(Settings::allowBurstDeviation())
		{
			p->init(JAWE::Random::randf(1.5, 2.5), m_timeDeviation.front());
			p->setDeviation(m_positionDeviation.front(), m_sizeDeviation.front(),
							m_colorDeviation.front());
		}
		else
			p->init(JAWE::Random::randf(1.5, 2.5));

		fill(p, rand(m_positionRange), &m_positions);
		fill(p, rand(m_sizeRange), &m_sizes);
		fill(p, rand(m_colorRange), &m_colors);

		p->setGravity(m_gravity.front());

		p->normalize();

		return p;
	}
}
