#pragma once

#ifndef GL_H
#define GLFW_INCLUDE_NONE
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#endif // !GL_H

#ifndef CAMERA_H
#include "../Camera.h"
#endif // !CAMERA_H

#include <iostream>
#include "glm/gtx/string_cast.hpp"

class Mesh
{
public:
	Mesh(Camera* pCamera, glm::vec3 position);
	virtual ~Mesh() {}
	virtual void Render() = 0;
	void Translate(glm::vec3 move);
	void Rotate(glm::vec3 rotation);
	void Scale(glm::vec3 scale);

protected:
	virtual void Initialize() = 0;

	bool _initialized = false;
	Camera* _pCamera = nullptr;
	glm::mat4 _modelMatrix = glm::mat4(1.0f);
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
};

