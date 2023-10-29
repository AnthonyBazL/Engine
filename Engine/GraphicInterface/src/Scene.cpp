#include "Scene.h"

Scene::Scene()
{
	_pCamera = new Camera();
	_meshes.push_back(new Triangle(_pCamera, glm::vec3(0.0f)));
	_meshes.push_back(new Triangle(_pCamera, glm::vec3(1.5f, 0.0f, 0.0f)));
	_meshes.push_back(new CustomMesh(_pCamera, glm::vec3(0.0f)));
}

Scene::~Scene()
{
}
