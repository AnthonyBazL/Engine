#pragma once
#include <string>
#include "Loader/ObjLoader.h"
#include "Loader/TextureLoader.h"

namespace Engine {
	__declspec(dllexport) void Print();
	__declspec(dllexport) void* LoadObjFile(std::string filePath);
	__declspec(dllexport) unsigned char* LoadTextureFile(std::string filePath);
}