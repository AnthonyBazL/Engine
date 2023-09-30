#include "Triangle.h"

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_position_buffer_data[] = {
   -0.5f, -0.75f, 0.0f,
   0.5f, -0.75f, 0.0f,
   0.0f,  0.75f, 0.0f,
};

// An array of 3 vectors which represents 3 colors
static const GLfloat g_vertex_color_buffer_data[] = {
   1.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f,  0.0f, 1.0f,
};

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

void Triangle::Render()
{
    if (!_initialized)
        Initialize();

    // Use our shader
    glUseProgram(_programID);

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

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
    glVertexAttribPointer(
        1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Triangle::Initialize()
{
    // Load Shaders
    _programID = ShaderLoader::LoadShaders("src/Shaders/SimpleVertexShader.vert", "src/Shaders/SimpleFragmentShader.frag");

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_position_buffer_data), g_vertex_position_buffer_data, GL_STATIC_DRAW);


    // This will identify our color buffer
    // Generate 1 buffer, put the resulting identifier in color buffer
    glGenBuffers(1, &_colorBuffer);
    // The following commands will talk about our 'colorbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_color_buffer_data), g_vertex_color_buffer_data, GL_STATIC_DRAW);

    _initialized = true;
}
