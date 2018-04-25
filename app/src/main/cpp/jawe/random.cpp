#include "random.h"

namespace JAWE {

	std::mt19937 Random::s_generator = std::mt19937(840331);
	std::mutex Random::s_mutex;
}
