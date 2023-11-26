#include "Mesh.h"

namespace Engine
{
	Mesh::Mesh(Camera* pCamera, Light* pLight, float* position)
	{
		_pCamera = pCamera;
		_pLight = pLight;
		Translate(position);
		_rotation = glm::vec3(0.0f);
		_scale = glm::vec3(1.0f);
		_pMeshData = new MeshData();
	}

	void Mesh::Translate(float* newPosition)
	{
		glm::vec3 newPos = glm::make_vec3(newPosition);
		glm::vec3 diff = newPos - _position;
		_position = newPos;
		_modelMatrix = glm::translate(_modelMatrix, diff);
	}

	/* TODO: Rotate issue with the following use case:
	*
	* Keep in mind (0, 0, 0) result
	* Put Y axis to 45 degree
	* Put Z axis to 45 degree
	* Reset Y axis to 0 degree
	* Reset Z axis to 0 degree
	* (0, 0, 0) isn't the same the beginning
	* It's due to the order of matrice multiplication
	*
	* TO TEST:
		glm::vec3 x = glm::vec3(1,0,0)*glm::radians(45.0f);
		glm::vec3 y = glm::vec3(0,1,0)*glm::radians(45.0f);
		glm::vec3 r = x+y;
		glm::mat4 m;
		m = glm::rotate(m, glm::length(r), glm::normalize(r));
	*/
	void Mesh::Rotate(float* applyRot)
	{
		float degree = 0.0f;
		glm::vec3 rotation = glm::make_vec3(applyRot);
		if (rotation.x != _rotation.x)
		{
			degree = abs(rotation.x - _rotation.x);
			if (rotation.x < _rotation.x)
				degree *= -1;

			_modelMatrix = glm::rotate(_modelMatrix, glm::radians(degree), glm::vec3(1.0f, 0.0f, 0.0f));
			_rotation.x = rotation.x;
		}

		if (rotation.y != _rotation.y)
		{
			degree = abs(rotation.y - _rotation.y);
			if (rotation.y < _rotation.y)
				degree *= -1;

			_modelMatrix = glm::rotate(_modelMatrix, glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
			_rotation.y = rotation.y;
		}

		if (rotation.z != _rotation.z)
		{
			degree = abs(rotation.z - _rotation.z);
			if (rotation.z < _rotation.z)
				degree *= -1;

			_modelMatrix = glm::rotate(_modelMatrix, glm::radians(degree), glm::vec3(0.0f, 0.0f, 1.0f));
			_rotation.z = rotation.z;
		}
	}

	void Mesh::Scale(float* newScale)
	{
		glm::vec3 scale = glm::make_vec3(newScale);
		glm::vec3 diff = scale - _scale;
		_scale = scale;
		_modelMatrix = glm::scale(_modelMatrix, diff + glm::vec3(1.0f));
	}
}