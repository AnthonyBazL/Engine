#pragma once

#include <iostream>
#include "../../includes/GLEW/GL/glew.h"
#include "../../includes/GLFW/glfw3.h"

#ifndef CAMERA_H
#include "../Components/Camera.h"
#endif // !CAMERA_H

#ifndef LIGHT_H
#include "../Components/Light.h"
#endif

#include "MeshData.h"

namespace Engine
{
	class Mesh
	{
	public:
		Mesh(float* position);
		virtual ~Mesh() {}
		_declspec(dllexport) void Translate(float* newPosition);
		_declspec(dllexport) void Rotate(float* applyRotation);
		_declspec(dllexport) void Scale(float* newScale);
		float GetShininess() { return _shininess; }
		void SetShininess(float shininess) { _shininess = shininess; }
		MeshData* GetMeshData() { return _pMeshData; }
		glm::mat4 GetModelMatrix() { return _modelMatrix; }

	protected:
		bool _initialized = false;
		MeshData* _pMeshData;
		glm::mat4 _modelMatrix = glm::mat4(1.0f);
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		// TODO: Create Material class
		float _shininess = 32;
	};
}