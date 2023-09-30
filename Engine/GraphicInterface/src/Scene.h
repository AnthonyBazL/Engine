#pragma once

#include <vector>
#include "Meshes/Primitives/Triangle.h"

class Scene
{
public:
	Scene();
	~Scene();
	std::vector<Mesh*> GetMeshes() { return _meshes; };

private:
	std::vector<Mesh*> _meshes;
};

