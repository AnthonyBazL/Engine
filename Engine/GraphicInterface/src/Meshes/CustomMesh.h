#pragma once

#ifndef MESH_H
#include "Mesh.h"
#endif // !MESH_H

#ifndef SHADER_LOADER_H
#include "../Shaders/ShaderLoader.h"
#endif // !SHADER_LOADER_H


namespace Engine {
	__declspec(dllimport) class ObjFileData;
	__declspec(dllimport) void* LoadObjFile(std::string filePath);
	__declspec(dllimport) unsigned char* LoadTextureFile(std::string filePath);
}

class CustomMesh : public Mesh
{
public:
	CustomMesh(Camera* pCamera, glm::vec3 position);
	~CustomMesh();

private:
	void Initialize() override;
	void Render() override;

	GLuint _vertexPositionBuffer = -1;
	GLuint _vertexUVBuffer = -1;
	GLuint _programID = -1;
	Engine::ObjFileData* _pObjFileData;
	unsigned int _textureID;
};

