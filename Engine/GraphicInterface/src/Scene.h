#pragma once

#include <vector>
#include "Meshes/Primitives/Triangle.h"
#include "Meshes/CustomMesh.h"

#ifndef CAMERA_H
#include "Components/Camera.h"
#endif // !CAMERA_H

#ifndef LIGHT_H
#include "Components/Light.h"
#endif

class Scene
{
public:
	Scene();
	~Scene();
	std::vector<Mesh*> GetMeshes() { return _meshes; }
	Camera* GetCamera() { return _pCamera; }
	Light* GetLight() { return _pLight; }

private:
	Camera* _pCamera;
	Light* _pLight;
	std::vector<Mesh*> _meshes;
};

