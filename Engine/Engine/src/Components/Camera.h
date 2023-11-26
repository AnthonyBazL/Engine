#pragma once
#include "Component.h"

namespace Engine
{
	class Camera : public Component
	{
	public:
		Camera(float* position);
		~Camera();
		void SetWorldPosition(float* position) override;
		_declspec(dllexport) void SetFov(float fov);
		_declspec(dllexport) void SetNear(float near);
		_declspec(dllexport) void SetFar(float far);
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
}
