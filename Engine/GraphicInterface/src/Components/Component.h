#pragma once
#ifndef GLM_H
#include <GLM/gtc/matrix_transform.hpp>
#endif

class Component
{
public:
	virtual void SetWorldPosition(glm::vec3 position);
	glm::vec3 GetWorldPosition() { return _worldPosition; }

protected:
	glm::vec3 _worldPosition;
};

