#pragma once

#ifndef GL_H
#define GLFW_INCLUDE_NONE
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#endif // !GL_H

#include <fstream>
#include <sstream>
#include <vector>

class ShaderLoader
{
public:
	static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
};

