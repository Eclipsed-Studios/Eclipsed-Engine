#pragma once 

#include "EclipsedEngine.Core.hpp"

namespace Eclipse
{
	class ECL_API SubSystem {
	public:
		virtual void Init() {};
		virtual void Execute() {};
	};
}