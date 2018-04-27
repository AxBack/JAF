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

		enum FACTOR_TYPE { SAME, OPPOSITE, OPPOSITE_X, OPPOSITE_Z };

		BalancedCollection<int> m_nrRockets;
		BalancedCollection<float> m_intervals;
		BalancedCollection<FACTOR_TYPE> m_factors;

		BalancedCollection<UINT> m_nrParticlesPerBurst;

		RocketCreator m_rocketCreator;
		BurstCreator m_burstCreator;
		TrailCreator m_trailCreator;

		void createRockets(Sequence& out);
		void createBursts(Sequence& out);
		void createTrails(Sequence& out);

	public:

		SequenceCreator()
		{
			m_nrRockets.push(1);
			m_nrRockets.push(2);
			m_nrRockets.push(3);
			m_nrRockets.push(4);

			m_intervals.push(0.0f);
			m_intervals.push(0.5f);
			m_intervals.push(1.0f);
			m_intervals.push(2.0f);

			m_factors.push(SAME);
			m_factors.push(OPPOSITE);
			m_factors.push(OPPOSITE_X);
			m_factors.push(OPPOSITE_Z);

			m_nrParticlesPerBurst.push(50);
			m_nrParticlesPerBurst.push(100);
			m_nrParticlesPerBurst.push(150);
			m_nrParticlesPerBurst.push(200);
		}

		void create(Sequence& out);

	};

};