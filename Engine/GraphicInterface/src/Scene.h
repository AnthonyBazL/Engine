#pragma once

#include <vector>
#include "Meshes/Primitives/Triangle.h"

#ifndef CAMERA_H
#include "Camera.h"
#endif // !CAMERA_H


class Scene
{
public:
	Scene();
	~Scene();
	std::vector<Mesh*> GetMeshes() { return _meshes; }
	Camera* GetCamera() { return _pCamera; }

private:
	Camera* _pCamera;
	std::vector<Mesh*> _meshes;
};

