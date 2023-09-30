#include "Scene.h"

Scene::Scene()
{
	_meshes.push_back(new Triangle());
}

Scene::~Scene()
{
}
