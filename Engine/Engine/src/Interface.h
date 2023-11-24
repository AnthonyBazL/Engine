#pragma once
#include <string>
#include "Loader/ObjLoader.h"
#include "Loader/TextureLoader.h"
#include "../Core.h"

namespace Engine {
	__declspec(dllexport) void Print();
	__declspec(dllexport) void* LoadObjFile(std::string filePath);
	__declspec(dllexport) void* LoadTextureFile(std::string filePath);
	__declspec(dllexport) void Initialize();
}