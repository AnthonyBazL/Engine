#pragma once
#include <string>
#include "Loader/ObjLoader.h"

namespace Engine {
	__declspec(dllexport) void Print();
	__declspec(dllexport) void* LoadFile(std::string filePath);
}