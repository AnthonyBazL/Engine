#include "Application.h"

namespace Engine {
    __declspec(dllimport) void Print();
}

int main()
{
    Engine::Print();
    auto pApp = new GraphicInterface::Application();
    pApp->Run();
    delete pApp;
}