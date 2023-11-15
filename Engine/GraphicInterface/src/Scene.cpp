#include "Scene.h"

Scene::Scene()
{
	_pCamera = new Camera(glm::vec3(0.0f, 0.0f, -10));
	_pLight = new Light(glm::vec3(-10.0f, 10.0f, 0.0f));
	_meshes.push_back(new Triangle(_pCamera, _pLight, glm::vec3(0.0f)));
	_meshes.push_back(new Triangle(_pCamera, _pLight, glm::vec3(1.5f, 0.0f, 0.0f)));
	_meshes.push_back(new CustomMesh(_pCamera, _pLight, glm::vec3(0.0f)));
}

Scene::~Scene()
{
}
