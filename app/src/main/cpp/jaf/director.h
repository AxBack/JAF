#pragma once

#include "../jawe/math/color.h"
#include "../jawe/path.h"
#include "../jawe/math/vector3.h"
#include "behaviour.h"
#include "sequence.h"
#include "sequence_creator.h"

namespace JAF {

	class Updater;

	class Director
	{
	private:

		typedef std::shared_ptr<Sequence> sequence_ptr;

		SequenceCreator m_creator;

		sequence_ptr m_pSequence;

	public:

		void init(std::mt19937& generator, Updater* pUpdater);

		void update(float dt);
	};
};