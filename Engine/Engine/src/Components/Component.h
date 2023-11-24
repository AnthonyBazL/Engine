#pragma once

#include "../../includes/GLM/gtx/string_cast.hpp"
#include "../../includes/GLM/gtc/type_ptr.hpp"
//#include "../../includes/GLM/gtc/matrix_transform.hpp"
//#include "../../includes/GLM/ext/vector_float3.hpp"
//#include "../../includes/GLM/gtc/type_ptr.hpp"

namespace Engine
{
	class Component
	{
	public:
		virtual void SetWorldPosition(float* position);
		float* GetWorldPosition() { return _worldPosition; }

	protected:
		float* _worldPosition;
	};
}

