#pragma once

#ifndef GL_H
#define GLFW_INCLUDE_NONE
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#endif // !GL_H

#ifndef CAMERA_H
#include "../Camera.h"
#endif // !CAMERA_H

class Mesh
{
public:
	Mesh(Camera* pCamera) { _pCamera = pCamera; }
	virtual ~Mesh() {}
	virtual void Render() = 0;

protected:
	virtual void Initialize() = 0;

	bool _initialized = false;
	Camera* _pCamera = nullptr;
	glm::mat4 _modelMatrix = glm::mat4(1.0f);
};

