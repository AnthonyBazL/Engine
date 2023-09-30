#pragma once

#ifndef GL_H
#define GLFW_INCLUDE_NONE
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#endif // !GL_H

class Mesh
{
public:
	Mesh() {};
	virtual ~Mesh() {};
	virtual void Render() = 0;

protected:
	virtual void Initialize() = 0;

	bool _initialized = false;
};

