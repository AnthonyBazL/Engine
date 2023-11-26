#include "CustomMesh.h"

namespace Engine
{
	CustomMesh::CustomMesh(Camera* pCamera, Light* pLight, float* position,
		std::string objFilePath, std::vector<std::string> textureFilesPath,
		std::string vertexShaderFilePath, std::string fragmentShaderFilePath)
		: Mesh(pCamera, pLight, position)
	{
		_objFilePath = objFilePath;
		_textureFilesPath = textureFilesPath;
		_vertexShaderFilePath = vertexShaderFilePath;
		_fragmentShaderFilePath = fragmentShaderFilePath;		

		// Load OBJ file
		_pMeshData->SetObjFileData(ObjLoader::LoadFile(_objFilePath));

		// Load texture
		for (int i = 0; i < _textureFilesPath.size(); ++i)
		{
			_pMeshData->AddTexturesData(TextureLoader::LoadFile(_textureFilesPath[i]));
		}

		// Specifiy shaders
		_pMeshData->SetVertexShader(_vertexShaderFilePath.c_str());
		_pMeshData->SetFragmentShader(_fragmentShaderFilePath.c_str());
	}

	CustomMesh::~CustomMesh()
	{
	}
}