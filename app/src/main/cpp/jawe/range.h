#pragma once

#include "random.h"

namespace JAWE {

	template <typename T>
	struct Range
	{
		T min, max;

		T clamp(T v) const
		{
			return v < min ? min : (v > max ? max : v);
		}
	};

}