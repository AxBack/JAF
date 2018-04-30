#pragma once

#include "balanced_collection.h"
#include "../jawe/path.h"
#include "../jawe/vector3.h"
#include "sequence.h"
#include "rocket_creator.h"
#include "trail_creator.h"

namespace JAF {

	class SequenceCreator
	{
	private:

		BalancedCollection<int> m_nrRockets;
		BalancedCollection<float> m_intervals;
		BalancedCollection<RocketBehaviour::OffsetType> m_offsets;

		BalancedCollection<UINT> m_nrBursts;
		BalancedCollection<UINT> m_nrParticles;

		RocketCreator m_rocketCreator;
		BurstCreator m_burstCreator;
		TrailCreator m_trailCreator;

		void createRockets(Sequence& out);
		void createBursts(RocketBehaviour* p);
		void createTrails(Sequence& out);

	public:

		SequenceCreator()
		{
			m_nrRockets.push(1);
			m_nrRockets.push(2);
			m_nrRockets.push(3);
			m_nrRockets.push(4);
			m_nrRockets.push(5);
			m_nrRockets.push(6);

			m_nrBursts.push(1);
			m_nrBursts.push(2);
			m_nrBursts.push(3);

			m_intervals.push(0.0f);
			m_intervals.push(0.25f);
			m_intervals.push(0.5f);
			m_intervals.push(0.75f);
			m_intervals.push(1.0f);

			m_offsets.push(RocketBehaviour::POINT);
			m_offsets.push(RocketBehaviour::LINE);
			m_offsets.push(RocketBehaviour::CIRCLE);

			m_nrParticles.push(50);
			m_nrParticles.push(100);
			m_nrParticles.push(150);
			m_nrParticles.push(200);
		}

		void create(Sequence& out);

	};

};