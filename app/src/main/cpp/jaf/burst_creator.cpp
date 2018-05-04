#include "burst_creator.h"
#include "settings.h"

namespace JAF {

	BurstCreator::BurstCreator()
		: PathBehaviourCreator(5)
	{
		{
			Release r = { {1, 2}, {1,2}, {1,2} };
			r.degrees.push(180.0f);
			r.interval.push(0.0f);
			r.nrPerSubBurst.push(INT_MAX);

			r.nrParticles.push(20, 0.75f);
			r.nrParticles.push(50, 0.75f);
			r.nrParticles.push(100);
			r.nrParticles.push(150);
			r.nrParticles.push(200);

			r.gravity.push({0,0,0});
			r.gravity.push({0,0,0});

			r.gravity.push({0,0,0}, 0.2f);
			r.gravity.push({0,-50,0});
			r.gravity.push({0,-100,0});

			r.releasePath.push(createPath(1, (Vector3[]){{0,0,0}, {0,1,0}}));

			m_releases.push(std::move(r));
		}

		{
			Release r = { {1, 2}, {1,2}, {1,2}, {0.1, 0.2} };
			r.forced.push_back(createPath(1, (Vector3[]){{0,0,0}}));
			r.degrees.push(45.0f, 0.5f);
			r.degrees.push(90.0f);

			r.interval.push(0.0f);
			r.interval.push(0.01f);
			r.interval.push(0.02f);
			r.interval.push(0.03f);
			r.interval.push(0.04f);
			r.interval.push(0.05f);

			r.nrParticles.push(50);
			r.nrParticles.push(80);
			r.nrParticles.push(100);

			r.nrPerSubBurst.push(5);
			r.nrPerSubBurst.push(10, 0.5f);
			r.nrPerSubBurst.push(20, 0.5f);
			r.nrPerSubBurst.push(30, 0.25f);

			r.releasePath.push(createPath(2, (Vector3[]){{0,0,0}, {0,100,0}}));
			r.releasePath.push(createPath(2, (Vector3[]){{0,0,0}, {0,200,0}}));
			r.releasePath.push(createPath(2, (Vector3[]){{0,0,0}, {0,300,0}}));

			r.gravity.push({0,0,0}, 0.25f);
			r.gravity.push({0,-50,0});
			r.gravity.push({0,-100,0});
			r.gravity.push({0,-150,0});
			r.gravity.push({0,-200,0});

			m_releases.push(std::move(r));
		}

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

		for(UINT i=1; i<=Settings::nrBursts(); ++i)
			m_nrBursts.push(i);

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
		p->init(JAWE::Random::randf(1.5, 2.5));
		fill(p, rand(pRelease->positionRange), &m_positions);
		fill(p, rand(pRelease->sizeRange), &m_sizes);
		fill(p, rand(pRelease->colorRange), &m_colors);

		p->setGravity(pRelease->gravity.front());

		for(auto& it : pRelease->forced)
			p->add(JAWE::Random::randf(pRelease->forcedWeight.min, pRelease->forcedWeight.max), it.get());

		p->setRelease(pRelease->degrees.front());
		p->normalize();
		return p;
	}

	BurstBehaviour* BurstCreator::create()
	{
		if(Settings::nrBursts() != m_nrBursts.size())
		{
			m_nrBursts.clear();
			for(UINT i=1; i<=Settings::nrBursts(); ++i)
				m_nrBursts.push(i);
		}

		BurstBehaviour* p = getBehaviour();
		if(Settings::allowBurstDeviation())
		{
			p->init(1.0f, m_timeDeviation.front());
			p->setDeviation(m_positionDeviation.front(), m_sizeDeviation.front(),
							m_colorDeviation.front());
		}
		else
			p->init(1.0f);

		Release* pRelease = m_releases.frontPtr();

		p->setRelease(0.0f);
		p->add(1.0f, pRelease->releasePath.front().get());

		UINT nrParticles = pRelease->nrParticles.front();
		UINT nrBursts = m_nrBursts.front();

		float factor = 1.0f / static_cast<float>(nrBursts);
		UINT nr = static_cast<UINT>(static_cast<float>(nrParticles) * factor);

		for(UINT i=0; i<nrBursts; ++i)
		{
			float interval = pRelease->interval.front();
			int nrPerSubBurst = 0;
			if(interval > 0)
			{
				nrPerSubBurst = pRelease->nrPerSubBurst.front();
			}
			p->add(nr, from(pRelease), interval, nrPerSubBurst);
		}

		return p;
	}
}
