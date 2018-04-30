#include "burst_creator.h"

namespace JAF {

	BurstCreator::BurstCreator()
		: PathBehaviourCreator(5)
	{
		{
			Release r = { {1, 2}, {1,2}, {1,2} };
			r.degrees.push(180.0f);
			m_releases.push(std::move(r));
		}

		{
			Release r = { {1, 2}, {1,2}, {1,2}, {0.1, 0.5} };
			r.forced.push_back(createPath(1, (Vector3[]){{0,0,0}}));
			r.degrees.push(45.0f);
			r.degrees.push(90.0f);
			m_releases.push(std::move(r));
		}

		m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {0,1000,0}}));
		m_positions.push(createPath(2, (Vector3[]){{0,0,0}, {0,100,0}}));
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
	}

	BurstBehaviour* BurstCreator::create()
	{
		if(m_pRelease == nullptr)
			step();

		BurstBehaviour* p = getBehaviour();

		p->init(2.0f);
		fill(p, rand(m_pRelease->positionRange), &m_positions);
		fill(p, rand(m_pRelease->sizeRange), &m_sizes);
		fill(p, rand(m_pRelease->colorRange), &m_colors);

		for(auto& it : m_pRelease->forced)
			p->add(JAWE::Random::randf(m_pRelease->forcedWeight.min, m_pRelease->forcedWeight.max), it);

		p->setRelease(m_pRelease->degrees.front());
		p->normalize();
		return p;
	}
}
