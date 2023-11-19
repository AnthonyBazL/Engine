#pragma once

#ifndef MESH_H
#include "Mesh.h"
#endif // !MESH_H

#ifndef SHADER_LOADER_H
#include "../Shaders/ShaderLoader.h"
#endif // !SHADER_LOADER_H

#include <GLM/gtc/type_ptr.hpp>
#include "../../../Engine/src/Loader/ObjLoader.h"
#include "../../../Engine/src/Loader/TextureLoader.h"

namespace Engine {
	__declspec(dllimport) class ObjFileData;
	__declspec(dllimport) class ObjectInformations;
	__declspec(dllimport) class TextureData;
	__declspec(dllimport) void* LoadObjFile(std::string filePath);
	__declspec(dllimport) void* LoadTextureFile(std::string filePath);
}

class CustomMesh : public Mesh
{
public:
	CustomMesh(Camera* pCamera, Light* pLight, glm::vec3 position);
	~CustomMesh();

private:
	void Initialize() override;
	void Render() override;

	GLuint* _vertexPositionBufferID;
	GLuint* _vertexUVBufferID;
	GLuint* _vertexNormalBufferID;
	GLuint _programID = -1;
	GLuint* _textureID;
	Engine::ObjFileData* _pObjFileData;
};

