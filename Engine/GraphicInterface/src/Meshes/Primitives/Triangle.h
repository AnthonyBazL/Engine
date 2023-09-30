#pragma once

#ifndef MESH_H
#include "../Mesh.h"
#endif // !MESH_H

#ifndef SHADER_LOADER_H
#include "../../Shaders/ShaderLoader.h"
#endif // !SHADER_LOADER_H



class Triangle : public Mesh
{
public:
	Triangle();
	~Triangle();

private:
	void Initialize() override;
	void Render() override;

	GLuint _vertexBuffer;
	GLuint _colorBuffer;
	GLuint _programID;
};

