#pragma once

#ifndef MESH_H
#include "../Mesh.h"
#endif // !MESH_H

#ifndef SHADER_LOADER_H
#include "../../Shaders/ShaderLoader.h"
#endif // !SHADER_LOADER_H

#ifndef GLM_H
#include <GLM/gtc/matrix_transform.hpp>
#endif



class Triangle : public Mesh
{
public:
	Triangle(Camera* pCamera, Light* pLight, glm::vec3 position);
	~Triangle();

private:
	void Initialize() override;
	void Render() override;

	GLuint _vertexBuffer = -1;
	GLuint _colorBuffer = -1;
	GLuint _programID = -1;
};

