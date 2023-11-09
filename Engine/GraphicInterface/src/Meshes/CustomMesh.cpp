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
    _pObjFileData = (Engine::ObjFileData*)Engine::LoadFile("C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\obj\\TheCube.obj");

    // Load Shaders
    _programID = ShaderLoader::LoadShaders("src/Shaders/CustomVertexShader.vert", "src/Shaders/CustomFragmentShader.frag");

    // VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // This will identify our vertex buffer
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexBuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, _pObjFileData->vertex_position_sorted.size() * sizeof(float), _pObjFileData->vertex_position_sorted.data(), GL_STATIC_DRAW);

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

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // Draw 
    if(_pObjFileData->face_triangle)
        glDrawArrays(GL_TRIANGLES, 0, _pObjFileData->vertex_position_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
    else
        glDrawArrays(GL_QUADS, 0, _pObjFileData->vertex_position_sorted.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
}