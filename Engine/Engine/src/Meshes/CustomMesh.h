#pragma once

#ifndef MESH_H
#include "Mesh.h"
#endif // !MESH_H

#ifndef SHADER_LOADER_H
#include "../Loader/ShaderLoader.h"
#endif // !SHADER_LOADER_H

#include "../../../Engine/src/Loader/ObjLoader.h"
#include "../../../Engine/src/Loader/TextureLoader.h"

namespace Engine 
{
	class CustomMesh : public Mesh
	{
	public:
		CustomMesh(float* position,
			std::string objFilePath, std::vector<std::string> textureFilesPath,
			std::string vertexShaderFilePath, std::string fragmentShaderFilePath);
		~CustomMesh();

	private:
		std::string _objFilePath;
		std::vector<std::string> _textureFilesPath;
		std::string _vertexShaderFilePath;
		std::string _fragmentShaderFilePath;
	};
}