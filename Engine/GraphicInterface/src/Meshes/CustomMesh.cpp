#include "CustomMesh.h"
#include "../../../Engine/src/Loader/ObjLoader.h"

CustomMesh::CustomMesh(Camera* pCamera, glm::vec3 position) : Mesh(pCamera, position)
{
}

CustomMesh::~CustomMesh()
{
}

void CustomMesh::Initialize()
{
    // Load OBJ file
    _pObjFileData = (Engine::ObjFileData*)Engine::LoadObjFile("C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\obj\\Test.obj");

    // Load texture
    unsigned char* textureData = Engine::LoadTextureFile("C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\textures\\test.jpg");// rubikscube.png");

    // Load Shaders
    _programID = ShaderLoader::LoadShaders("src/Shaders/CustomVertexShader.vert", "src/Shaders/CustomFragmentShader.frag");

    // VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // This will identify our positions buffer
    // Generate 1 buffer, put the resulting identifier in _vertexPositionBuffer
    glGenBuffers(1, &_vertexPositionBuffer);
    // The following commands will talk about our '_vertexPositionBuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexPositionBuffer);
    // Give our buffer to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, _pObjFileData->positions_sorted.size() * sizeof(float), _pObjFileData->positions_sorted.data(), GL_STATIC_DRAW);


    // This will identify our vertex buffer
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexUVBuffer);
    // The following commands will talk about our '_vertexPositionBuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexUVBuffer);
    // Give our buffer to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, _pObjFileData->uvs_sorted.size() * sizeof(float), _pObjFileData->uvs_sorted.data(), GL_STATIC_DRAW);

    // Texture config
    if (textureData)
    {
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenTextures(1, &_textureID);
        glBindTexture(GL_TEXTURE_2D, _textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1000, 1000/*1920, 1350*//*1536, 2048*/, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Bind texture
        glBindTexture(GL_TEXTURE_2D, _textureID);
    }
    else
    {
        std::cout << "Failed to load texture file" << std::endl;
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

    // 1st attribute buffer : vertices positions
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexPositionBuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, _vertexUVBuffer);
    glVertexAttribPointer(
        1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // Draw 
    if(_pObjFileData->face_triangle)
        glDrawArrays(GL_TRIANGLES, 0, _pObjFileData->positions_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
    else
        glDrawArrays(GL_QUADS, 0, _pObjFileData->positions_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}