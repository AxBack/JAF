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

		T smoothstep(T v) const
		{
			if(v <= min)
				return 0.0f;
			else if(v >= max)
				return 1.0f;

			return (v-min) / (max - min);
		}
	};

}