#pragma once

#ifndef GLM_H
#include <GLM/gtc/matrix_transform.hpp>
#endif

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 GetViewMatrix() { return _viewMatrix; }
	glm::mat4 GetProjectionMatrix() { return _projectionMatrix; }
	void SetPosition(glm::vec3 position);
	glm::vec3 GetWorldPosition() { return _worldPosition; }

private:
	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
	glm::vec3 _worldPosition;
	glm::vec3 _target;
	float _fov;
	float _aspectRatio;
	float _near;
	float _far;
};

