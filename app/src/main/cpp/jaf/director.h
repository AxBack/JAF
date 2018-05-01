#pragma once

#include "../jawe/color.h"
#include "../jawe/path.h"
#include "../jawe/vector3.h"
#include "behaviour.h"
#include "sequence.h"
#include "sequence_creator.h"

namespace JAF {

	class Updater;

	class Director
	{
	private:

		typedef std::shared_ptr<Sequence> sequence_ptr;

		std::mt19937 m_generator;

		SequenceCreator m_creator;

		sequence_ptr m_pSequence;

	public:

		void init(std::mt19937& generator, Updater* pUpdater);

		void update(float dt);
	};
};