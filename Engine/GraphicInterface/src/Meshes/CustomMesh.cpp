#include "CustomMesh.h"


CustomMesh::CustomMesh(Camera* pCamera, Light* pLight, glm::vec3 position) : Mesh(pCamera, pLight, position)
{
}

CustomMesh::~CustomMesh()
{
}

void CustomMesh::Initialize()
{
    // Load OBJ file
    _pObjFileData = (Engine::ObjFileData*)Engine::LoadObjFile("C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\obj\\MultipleObject.obj");

    // Load texture
    const int objectCount = _pObjFileData->objects.size();
    std::vector<Engine::TextureData*> textureData;
    textureData.push_back((Engine::TextureData*)Engine::LoadTextureFile("C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\textures\\test.jpg"));
    textureData.push_back((Engine::TextureData*)Engine::LoadTextureFile("C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\textures\\suzanne.jpg"));
    textureData.push_back((Engine::TextureData*)Engine::LoadTextureFile("C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\textures\\rock.jpg"));

    _textureID = new unsigned int[objectCount];

    // Load Shaders
    _programID = ShaderLoader::LoadShaders("src/Shaders/CustomVertexShader.vert", "src/Shaders/CustomFragmentShader.frag");

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
        // The following commands will talk about our '_vertexPositionBuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vertexPositionBufferID[i]);
        // Give our buffer to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, _pObjFileData->objects[i]->positions_sorted.size() * sizeof(float), _pObjFileData->objects[i]->positions_sorted.data(), GL_STATIC_DRAW);

        // Vertex UVs
        // The following commands will talk about our '_vertexPositionBuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vertexUVBufferID[i]);
        // Give our buffer to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, _pObjFileData->objects[i]->uvs_sorted.size() * sizeof(float), _pObjFileData->objects[i]->uvs_sorted.data(), GL_STATIC_DRAW);

        // Vertex normals
        // The following commands will talk about our '_vertexPositionBuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vertexNormalBufferID[i]);
        // Give our buffer to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, _pObjFileData->objects[i]->normals_sorted.size() * sizeof(float), _pObjFileData->objects[i]->normals_sorted.data(), GL_STATIC_DRAW);

        // Texture config
        if (textureData[i])
        {
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 mvp = _pCamera->GetProjectionMatrix() * _pCamera->GetViewMatrix() * _modelMatrix; // Remember, matrix multiplication is the other way around

    // Get a handle for our "MVP" uniform
    // Only during the initialisation
    GLuint MatrixID = glGetUniformLocation(_programID, "MVP");

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    // Pass light position to shader
    GLuint lightPositionID = glGetUniformLocation(_programID, "u_lightPosition");
    glUniform3fv(lightPositionID, 1, glm::value_ptr(_pLight->GetWorldPosition()));

    // Pass diffuse light intensity to shader
    GLuint diffuseLightIntensityID = glGetUniformLocation(_programID, "u_diffuseLightIntensity");
    glUniform1f(diffuseLightIntensityID, _pLight->GetDiffuseIntensity());

    // Pass diffuse light intensity to shader
    GLuint ambiantLightIntensityID = glGetUniformLocation(_programID, "u_ambiantLightIntensity");
    glUniform1f(ambiantLightIntensityID, _pLight->GetAmbiantIntensity());

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
            2,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glBindTexture(GL_TEXTURE_2D, _textureID[i]);

        // Draw 
        if(_pObjFileData->face_triangle)
            glDrawArrays(GL_TRIANGLES, 0, _pObjFileData->objects[i]->positions_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
        else
            glDrawArrays(GL_QUADS, 0, _pObjFileData->objects[i]->positions_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
}