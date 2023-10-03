#include "Scene.h"

Scene::Scene()
{
	_pCamera = new Camera();
	_meshes.push_back(new Triangle(_pCamera));
}

Scene::~Scene()
{
}
