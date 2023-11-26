#pragma once
#include "../Loader/ObjLoader.h"
#include "../Loader/TextureLoader.h"
#include "../../includes/GLEW/GL/glew.h"

namespace Engine
{
	struct MeshData
	{
	public:
		void SetObjFileData(ObjFileData* pObjFileData) 
		{
			_pObjFileData = pObjFileData; 
#if USE_OPENGL // OpenGL specific
			const int objectCount = GetObjectCount();
			if (objectCount != 0)
			{
				_textureID = new GLuint[objectCount];
				_vertexPositionBufferID = new GLuint[objectCount];
				_vertexUVBufferID = new GLuint[objectCount];
				_vertexNormalBufferID = new GLuint[objectCount];
			}
#endif
		}
		void AddTexturesData(TextureData* pTextureData) { _texturesData.push_back(pTextureData); }
		void SetVertexShader(const char* vertexShaderPath) { _vertexShaderPath = vertexShaderPath; }
		void SetFragmentShader(const char* fragmentShaderPath) { _fragmentShaderPath = fragmentShaderPath; }
		void SetInitialized(bool initialized) { _initialized = initialized; }
		bool IsInitialized() { return _initialized; }
		uint8_t GetObjectCount() {
			if (_pObjFileData)
			{
				return _pObjFileData->objects.size();
			}
			else
				return 0;
		}
		ObjectInformations* GetObjectData(uint8_t index)
		{
			if (_pObjFileData)
			{
				return _pObjFileData->objects[index];
			}
			else
				return 0;
		}
		TextureData* GetTextureDatas(uint16_t index)
		{
			if (index < _texturesData.size())
				return _texturesData[index];
			else
				return nullptr;
		}
		const char* GetVertexShaderPath() { return _vertexShaderPath; }
		const char* GetFragmentShaderPath() { return _fragmentShaderPath; }
		bool FaceTriangulated() { return _pObjFileData->face_triangle; }
#if USE_OPENGL // OpenGL specific
		GLuint* GetVertexPositionBufferID() { return _vertexPositionBufferID; }
		GLuint* GetVertexUVBufferID() { return _vertexUVBufferID; }
		GLuint* GetVertexNormalBufferID() { return _vertexNormalBufferID; }
		GLuint GetProgramID() { return _programID; }
		GLuint* GetTextureID() { return _textureID; }
		void SetProgramID(GLuint programID) { _programID = programID; }
#endif

	private:
		bool _initialized = false;
		ObjFileData* _pObjFileData;
		std::vector<TextureData*> _texturesData;
		const char* _vertexShaderPath;
		const char* _fragmentShaderPath;
#if USE_OPENGL // OpenGL specific
		GLuint* _vertexPositionBufferID = nullptr;
		GLuint* _vertexUVBufferID = nullptr;
		GLuint* _vertexNormalBufferID = nullptr;
		GLuint _programID = -1;
		GLuint* _textureID = nullptr;
#endif
	};
}

