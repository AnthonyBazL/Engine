#pragma once
#include "Component.h"

class Camera : public Component
{
public:
	Camera(glm::vec3 position);
	~Camera();
	void SetWorldPosition(glm::vec3 position) override;
	void SetFov(float fov);
	void SetNear(float near);
	void SetFar(float far);
	glm::mat4 GetViewMatrix() { return _viewMatrix; }
	glm::mat4 GetProjectionMatrix() { return _projectionMatrix; }
	float GetFov() { return _fov; }
	float GetNear() { return _near; }
	float GetFar() { return _far; }

private:
	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
	glm::vec3 _target;
	float _fov;
	float _aspectRatio;
	float _near;
	float _far;
};

