#include "rocket_creator.h"

namespace JAF {

	RocketCreator::RocketCreator()
			: PathBehaviourCreator(2)
	{

		m_burstCreator.init();

		m_creators.push([=](RocketBehaviour* p){
			UINT nrBursts = m_nrBursts.front();
			for(UINT i=0; i<nrBursts; ++i)
				p->add(m_nrParticles.front(), m_burstCreator.create());
		});
		m_creators.push([=](RocketBehaviour* p){
			p->add(1U, m_slowBurstCreator.create());
		});

		m_timeDeviation.push(0.0f);
		m_timeDeviation.push(0.1f);
		m_timeDeviation.push(0.2f);

		m_positionDeviation.push(0.0f);
		m_positionDeviation.push(0.1f);
		m_positionDeviation.push(0.2f);
		m_positionDeviation.push(0.3f);

		m_nrParticles.push(20, 0.75f);
		m_nrParticles.push(50, 0.75f);
		m_nrParticles.push(100);
		m_nrParticles.push(150);
		m_nrParticles.push(200);

		m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {-300,500,0}, {300,1250,0}}));
		m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {300,500,0}, {-300,1250,0}}));
		m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {0,1000,-300}, {0,1250,300}}));
		m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {0,1000,300}, {0,1250,-300}}));
		m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {0,1000,600}, {0,1500,0}}));
		m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {0,1000,-600}, {0,1500,0}}));
		m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {600,1000,0}, {0,1500,0}}));
		m_positions.push(createPath(3, (Math::Vector3[]){{0,0,0}, {-600,1000,0}, {0,1500,0}}));

		m_positions.push(createPath(2, (Math::Vector3[]){{0,0,0}, {0,1500,-250}}));
		m_positions.push(createPath(2, (Math::Vector3[]){{0,0,0}, {0,1500,250}}));
		m_positions.push(createPath(2, (Math::Vector3[]){{0,0,0}, {-250,1500,0}}));
		m_positions.push(createPath(2, (Math::Vector3[]){{0,0,0}, {250,1500,0}}));

		m_positions.push(createPath(4, (Math::Vector3[]){{0,0,0}, {0,400,500}, {500,800,0}, {0,1200,-200}}), 2.0f);
		m_positions.push(createPath(4, (Math::Vector3[]){{0,0,0}, {0,400,-500}, {-500,800,0}, {0,1200,200}}), 2.0f);
		m_positions.push(createPath(4, (Math::Vector3[]){{0,0,0}, {-500,400,0}, {0,800,500}, {200,1200,0}}), 2.0f);
		m_positions.push(createPath(4, (Math::Vector3[]){{0,0,0}, {500,400,0}, {0,800,-500}, {-200,1200,0}}), 2.0f);
	}

	RocketBehaviour* RocketCreator::create()
	{
		if(Settings::nrBursts() != m_nrBursts.size())
		{
			m_nrBursts.clear();
			for(UINT i=1; i<=Settings::nrBursts(); ++i)
				m_nrBursts.push(i);
		}

		m_burstCreator.step();
		m_trailCreator.step();

		RocketBehaviour* p = getBehaviour();
		p->init(JAWE::Random::randf(2.0f, 3.0f), Settings::allowRocketDeviation() ?  m_timeDeviation.front() : 0);
		fill(p, JAWE::Random::randi(1,2), &m_positions);
		if(Settings::allowRocketDeviation())
			p->setPositionDeviation(m_positionDeviation.front());
		p->normalize();

		m_creators.front()(p);

		p->add(0.025f, m_trailCreator.create());

		return p;
	}
}