#pragma once

#include <cstdint>

#include "../System/staticvector.h"

namespace Render
{
	struct SkeletonFragmentReindex
	{
		//unsigned int meshCheckSum[4]; //128-bit
		StaticVector< uint32_t > originalIndices;
	};
};