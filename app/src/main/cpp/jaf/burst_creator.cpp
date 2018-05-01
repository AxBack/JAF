#include "burst_creator.h"
#include "settings.h"

namespace JAF {

	BurstCreator::BurstCreator()
		: PathBehaviourCreator(5)
	{
		m_pImmediate = createPath(2, (Vector3[]){{0,0,0}, {0,1,0}});

		{
			Release r = { {1, 2}, {1,2}, {1,2} };
			r.degrees.push(180.0f);
			m_releases.push(std::move(r));
		}

		{
			Release r = { {1, 2}, {1,2}, {1,2}, {0.1, 0.2} };
			r.forced.push_back(createPath(1, (Vector3[]){{0,0,0}}));
			r.degrees.push(45.0f);
			r.degrees.push(90.0f);
			m_releases.push(std::move(r));
		}

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

		m_nrBursts.push(1);
		m_nrBursts.push(2);
		m_nrBursts.push(3);

		m_nrParticles.push(50);
		m_nrParticles.push(100);
		m_nrParticles.push(150);
		m_nrParticles.push(200);

		for(float v=0.0f; v < 0.6f; v+=0.1f)
		{
			m_timeDeviation.push(v);
			m_positionDeviation.push(v);
			m_sizeDeviation.push(v);
			m_colorDeviation.push(v);
		}
	}

	Behaviour* BurstCreator::from(Release* pRelease)
	{
		BurstBehaviour* p = getBehaviour();
		p->init(2.0f);
		fill(p, rand(pRelease->positionRange), &m_positions);
		fill(p, rand(pRelease->sizeRange), &m_sizes);
		fill(p, rand(pRelease->colorRange), &m_colors);

		for(auto& it : pRelease->forced)
			p->add(JAWE::Random::randf(pRelease->forcedWeight.min, pRelease->forcedWeight.max), it.get());

		p->setRelease(pRelease->degrees.front());
		p->normalize();
		return p;
	}

	BurstBehaviour* BurstCreator::create()
	{
		BurstBehaviour* p = getBehaviour();
		if(Settings::allowBurstDeviation())
		{
			p->init(JAWE::Random::randf(0.4, 0.7), m_timeDeviation.front());
			p->setDeviation(m_positionDeviation.front(), m_sizeDeviation.front(),
							m_colorDeviation.front());
		}
		else
			p->init(JAWE::Random::randf(0.4, 0.7));

		p->setRelease(0.0f);
		p->add(1.0f, m_pImmediate.get());


		UINT nrParticles = m_nrParticles.front();
		UINT nrBursts = m_nrBursts.front();

		float factor = 1.0f / static_cast<float>(nrBursts);
		UINT nr = static_cast<UINT>(static_cast<float>(nrParticles) * factor);

		Release* pRelease = m_releases.frontPtr();
		for(UINT i=0; i<nrBursts; ++i)
			p->add(nr, from(pRelease));

		return p;
	}
}
