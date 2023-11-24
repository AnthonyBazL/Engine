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
	}

	CustomMesh::~CustomMesh()
	{
	}

	void CustomMesh::Initialize()
	{
		// Load OBJ file
		_pObjFileData = (Engine::ObjFileData*)Engine::LoadObjFile(_objFilePath);

		// Load texture
		const int objectCount = _pObjFileData->objects.size();
		std::vector<Engine::TextureData*> textureData;

		for (int i = 0; i < _textureFilesPath.size(); ++i)
		{
			textureData.push_back((Engine::TextureData*)Engine::LoadTextureFile(_textureFilesPath[i]));
		}

		_textureID = new GLuint[objectCount];

		// Load Shaders
		_programID = ShaderLoader::LoadShaders(_vertexShaderFilePath.c_str(), _fragmentShaderFilePath.c_str());

		// VAO
		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		_vertexPositionBufferID = new GLuint[objectCount];
		_vertexUVBufferID = new GLuint[objectCount];
		_vertexNormalBufferID = new GLuint[objectCount];

		// This will identify our positions buffer
		// Generate 1 buffer per object, put the resulting identifier in _vertexPositionBufferID array
		glGenBuffers(objectCount, _vertexPositionBufferID);
		// This will identify our vertex buffer
		// Generate 1 buffer per object, put the resulting identifier in _vertexUVBufferID array
		glGenBuffers(objectCount, _vertexUVBufferID);
		// This will identify our vertex buffer
		// Generate 1 buffer per object, put the resulting identifier in _vertexNormalBufferID array
		glGenBuffers(objectCount, _vertexNormalBufferID);
		// Generate as many texture as the object has. I consider one texture per object
		glGenTextures(objectCount, _textureID);

		for (int i = 0; i < objectCount; ++i)
		{
			// Vertex positions
			// The following commands will talk about our '_vertexPositionBufferID' buffer
			glBindBuffer(GL_ARRAY_BUFFER, _vertexPositionBufferID[i]);
			// Give our buffer to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, _pObjFileData->objects[i]->positions_sorted.size() * sizeof(float), _pObjFileData->objects[i]->positions_sorted.data(), GL_STATIC_DRAW);

			// Vertex UVs
			// The following commands will talk about our '_vertexUVBufferID' buffer
			glBindBuffer(GL_ARRAY_BUFFER, _vertexUVBufferID[i]);
			// Give our buffer to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, _pObjFileData->objects[i]->uvs_sorted.size() * sizeof(float), _pObjFileData->objects[i]->uvs_sorted.data(), GL_STATIC_DRAW);

			// Vertex normals
			// The following commands will talk about our '_vertexNormalBufferID' buffer
			glBindBuffer(GL_ARRAY_BUFFER, _vertexNormalBufferID[i]);
			// Give our buffer to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, _pObjFileData->objects[i]->normals_sorted.size() * sizeof(float), _pObjFileData->objects[i]->normals_sorted.data(), GL_STATIC_DRAW);

			// Texture config
			if (textureData[i])
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glBindTexture(GL_TEXTURE_2D, _textureID[i]); // Select the texture of the first object we want to render
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData[i]->width, textureData[i]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData[i]->data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				std::cout << "Failed to load texture file" << std::endl;
			}
		}

		glEnable(GL_DEPTH_TEST);

		_initialized = true;
	}

	void CustomMesh::Render()
	{
		if (!_initialized)
			Initialize();

		// Use our shader
		glUseProgram(_programID);

		GLuint modelID = glGetUniformLocation(_programID, "u_model");
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &_modelMatrix[0][0]);
		GLuint viewID = glGetUniformLocation(_programID, "u_view");
		glUniformMatrix4fv(viewID, 1, GL_FALSE, &_pCamera->GetViewMatrix()[0][0]);
		GLuint projectionID = glGetUniformLocation(_programID, "u_projection");
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, &_pCamera->GetProjectionMatrix()[0][0]);

		// Pass light position to shader
		GLuint lightPositionID = glGetUniformLocation(_programID, "u_lightPosition");
		glUniform3fv(lightPositionID, 1, _pLight->GetWorldPosition());

		// Pass camera position to shader
		GLuint cameraPositionID = glGetUniformLocation(_programID, "u_cameraPosition");
		glUniform3fv(cameraPositionID, 1, _pCamera->GetWorldPosition());

		// Pass diffuse light intensity to shader
		GLuint diffuseLightIntensityID = glGetUniformLocation(_programID, "u_diffuseLightIntensity");
		glUniform1f(diffuseLightIntensityID, _pLight->GetDiffuseIntensity());

		// Pass ambiant light intensity to shader
		GLuint ambiantLightIntensityID = glGetUniformLocation(_programID, "u_ambiantLightIntensity");
		glUniform1f(ambiantLightIntensityID, _pLight->GetAmbiantIntensity());

		// Pass specular light intensity to shader
		GLuint specularLightIntensityID = glGetUniformLocation(_programID, "u_specularLightIntensity");
		glUniform1f(specularLightIntensityID, _pLight->GetSpecularIntensity());

		// Pass shininess of object to shader
		GLuint shininessID = glGetUniformLocation(_programID, "u_shininess");
		glUniform1f(shininessID, _shininess);

		int objectCount = _pObjFileData->objects.size();
		for (int i = 0; i < objectCount; ++i)
		{
			// 1st attribute buffer : vertices positions
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, _vertexPositionBufferID[i]);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			// 2nd attribute buffer : vertices UVs
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, _vertexUVBufferID[i]);
			glVertexAttribPointer(
				1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
				2,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			// 3rd attribute buffer : vertices normals
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, _vertexNormalBufferID[i]);
			glVertexAttribPointer(
				2,                  // attribute 2. No particular reason for 2, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glBindTexture(GL_TEXTURE_2D, _textureID[i]);

			// Draw 
			if (_pObjFileData->face_triangle)
				glDrawArrays(GL_TRIANGLES, 0, _pObjFileData->objects[i]->positions_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
			else
				glDrawArrays(GL_QUADS, 0, _pObjFileData->objects[i]->positions_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		}
	}
}