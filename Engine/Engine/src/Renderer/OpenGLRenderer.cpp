#if USE_OPENGL
#include "OpenGLRenderer.h"

namespace Engine
{
    OpenGLRenderer::OpenGLRenderer(Scene* pScene) : Renderer(pScene)
    {
    }

    void OpenGLRenderer::StartRendering()
	{
        int windowCreated = CreateWindow();
        if(windowCreated != -1) Render();
	}

	void OpenGLRenderer::StopRendering()
	{

	}

    int OpenGLRenderer::CreateWindow()
    {
        // Initialise GLFW
        glewExperimental = true; // Needed for core profile
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            return -1;
        }

        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

        // Open a window and create its OpenGL context
        _pWnd = glfwCreateWindow(1280, 720, "Graphic Interface (OpenGL)", NULL, NULL);
        if (_pWnd == NULL) {
            fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(_pWnd);

        // Initialize GLEW
        //glewExperimental = true; // Needed in core profile
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
            return -1;
        }

        return 0;
    }

    int OpenGLRenderer::Render()
    {
        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(_pWnd, GLFW_STICKY_KEYS, GL_TRUE);

        _pGUIManager = new ImGuiManager(_pWnd, _pScene);

        do 
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (Mesh* pMesh : _pScene->GetMeshes())
            {
                DrawMesh(pMesh);
            }

            // ImGui rendering
            _pGUIManager->Render();

            // Swap buffers
            glfwSwapBuffers(_pWnd);
            glfwPollEvents();

            // TODO: Remove, only debugging purpose
            double oldMousePosX = _mousePosX;
            double oldMousePosY = _mousePosY;
            glfwGetCursorPos(_pWnd, &_mousePosX, &_mousePosY);

            //if (oldMousePosX != _mousePosX || oldMousePosY != _mousePosY)
            //    std::cout << "Mouse Position (" << _mousePosX << ", " << _mousePosY << ")" << std::endl;

        } // Check if the ESC key was pressed or the window was closed
        while (glfwGetKey(_pWnd, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(_pWnd) == 0);

        delete _pGUIManager;

        glfwTerminate();

        return 0;
    }

    void OpenGLRenderer::CleanUp()
    {
    }

    void OpenGLRenderer::DrawMesh(Mesh* pMesh)
    {
        MeshData* pMeshData = pMesh->GetMeshData();
        bool meshDataPrepared = true;
        if (!pMeshData->IsInitialized())
            meshDataPrepared = PrepareMeshData(pMeshData);

        // There is object well deserialized from Obj file, prepared to be processed
        if (meshDataPrepared && pMeshData->GetObjectCount() > 0)
        {
            // Use our shader
            GLuint programID = pMeshData->GetProgramID();
            glUseProgram(programID);

            GLuint modelID = glGetUniformLocation(programID, "u_model");
            glUniformMatrix4fv(modelID, 1, GL_FALSE, &pMesh->GetModelMatrix()[0][0]);
            Camera* pCamera = _pScene->GetCamera();
            GLuint viewID = glGetUniformLocation(programID, "u_view");
            glUniformMatrix4fv(viewID, 1, GL_FALSE, &pCamera->GetViewMatrix()[0][0]);
            GLuint projectionID = glGetUniformLocation(programID, "u_projection");
            glUniformMatrix4fv(projectionID, 1, GL_FALSE, &pCamera->GetProjectionMatrix()[0][0]);

            // Pass light position to shader
            Light* pLight = _pScene->GetLight();
            GLuint lightPositionID = glGetUniformLocation(programID, "u_lightPosition");
            glUniform3fv(lightPositionID, 1, pLight->GetWorldPosition());

            // Pass camera position to shader
            GLuint cameraPositionID = glGetUniformLocation(programID, "u_cameraPosition");
            glUniform3fv(cameraPositionID, 1, pCamera->GetWorldPosition());

            // Pass diffuse light intensity to shader
            GLuint diffuseLightIntensityID = glGetUniformLocation(programID, "u_diffuseLightIntensity");
            glUniform1f(diffuseLightIntensityID, pLight->GetDiffuseIntensity());

            // Pass ambiant light intensity to shader
            GLuint ambiantLightIntensityID = glGetUniformLocation(programID, "u_ambiantLightIntensity");
            glUniform1f(ambiantLightIntensityID, pLight->GetAmbiantIntensity());

            // Pass specular light intensity to shader
            GLuint specularLightIntensityID = glGetUniformLocation(programID, "u_specularLightIntensity");
            glUniform1f(specularLightIntensityID, pLight->GetSpecularIntensity());

            // Pass shininess of object to shader
            GLuint shininessID = glGetUniformLocation(programID, "u_shininess");
            glUniform1f(shininessID, pMesh->GetShininess());

            int objectCount = pMeshData->GetObjectCount();
            for (int i = 0; i < objectCount; ++i)
            {
                // 1st attribute buffer : vertices positions
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, pMeshData->GetVertexPositionBufferID()[i]);
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
                glBindBuffer(GL_ARRAY_BUFFER, pMeshData->GetVertexUVBufferID()[i]);
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
                glBindBuffer(GL_ARRAY_BUFFER, pMeshData->GetVertexNormalBufferID()[i]);
                glVertexAttribPointer(
                    2,                  // attribute 2. No particular reason for 2, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );

                glBindTexture(GL_TEXTURE_2D, pMeshData->GetTextureID()[i]);

                // Draw 
                if (pMeshData->FaceTriangulated())
                    glDrawArrays(GL_TRIANGLES, 0, pMeshData->GetObjectData(i)->positions_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
                else
                    glDrawArrays(GL_QUADS, 0, pMeshData->GetObjectData(i)->positions_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle

                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
                glDisableVertexAttribArray(2);
            }
        }
    }

    bool OpenGLRenderer::PrepareMeshData(MeshData* pMeshData)
    {
        const int objectCount = pMeshData->GetObjectCount();
        if (objectCount == 0)
        {
            std::cout << "[WARNING] No object to render in this mesh" << std::endl;
            pMeshData->SetInitialized(true);
            return false;
        }

        // Load Shaders
        pMeshData->SetProgramID(ShaderLoader::LoadShaders(pMeshData->GetVertexShaderPath(), pMeshData->GetFragmentShaderPath()));

        // VAO
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        // This will identify our positions buffer
        // Generate 1 buffer per object, put the resulting identifier in _vertexPositionBufferID array
        GLuint* vertexPositionID = pMeshData->GetVertexPositionBufferID();
        glGenBuffers(objectCount, vertexPositionID);
        // This will identify our vertex buffer
        // Generate 1 buffer per object, put the resulting identifier in _vertexUVBufferID array
        GLuint* vertexBufferID = pMeshData->GetVertexUVBufferID();
        glGenBuffers(objectCount, vertexBufferID);
        // This will identify our vertex buffer
        // Generate 1 buffer per object, put the resulting identifier in _vertexNormalBufferID array
        GLuint* vertexNormalID = pMeshData->GetVertexNormalBufferID();
        glGenBuffers(objectCount, vertexNormalID);
        // Generate as many texture as the object has. I consider one texture per object
        GLuint* textureID = pMeshData->GetTextureID();
        glGenTextures(objectCount, textureID);

        for (int i = 0; i < objectCount; ++i)
        {
            ObjectInformations* pObjectData = pMeshData->GetObjectData(i);
            // Vertex positions
            // The following commands will talk about our '_vertexPositionBufferID' buffer
            glBindBuffer(GL_ARRAY_BUFFER, vertexPositionID[i]);
            // Give our buffer to OpenGL.
            glBufferData(GL_ARRAY_BUFFER, pObjectData->positions_sorted.size() * sizeof(float), pObjectData->positions_sorted.data(), GL_STATIC_DRAW);

            // Vertex UVs
            // The following commands will talk about our '_vertexUVBufferID' buffer
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID[i]);
            // Give our buffer to OpenGL.
            glBufferData(GL_ARRAY_BUFFER, pObjectData->uvs_sorted.size() * sizeof(float), pObjectData->uvs_sorted.data(), GL_STATIC_DRAW);

            // Vertex normals
            // The following commands will talk about our '_vertexNormalBufferID' buffer
            glBindBuffer(GL_ARRAY_BUFFER, vertexNormalID[i]);
            // Give our buffer to OpenGL.
            glBufferData(GL_ARRAY_BUFFER, pObjectData->normals_sorted.size() * sizeof(float), pObjectData->normals_sorted.data(), GL_STATIC_DRAW);

            // Texture config
            TextureData* textureData = pMeshData->GetTextureDatas(i);
            if (textureData)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glBindTexture(GL_TEXTURE_2D, textureID[i]); // Select the texture of the first object we want to render
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData->width, textureData->height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData->data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture file" << std::endl;
            }
        }

        glEnable(GL_DEPTH_TEST);

        pMeshData->SetInitialized(true);
    }
}
#endif