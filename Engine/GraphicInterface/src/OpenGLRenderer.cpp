#include "OpenGLRenderer.h"

namespace GraphicInterface
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
        _pWnd = glfwCreateWindow(1280, 720, "Graphic Interface", NULL, NULL);
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

        do {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (const auto& mesh : _pScene->GetMeshes())
            {
                mesh->Render();
            }

            // ImGui rendering
            _pGUIManager->Render();

            // Swap buffers
            glfwSwapBuffers(_pWnd);
            glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed
        while (glfwGetKey(_pWnd, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(_pWnd) == 0);

        delete _pGUIManager;

        glfwTerminate();

        return 0;
    }
}