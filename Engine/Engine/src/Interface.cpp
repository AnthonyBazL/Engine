#include "Interface.h"
#include <stdio.h>

namespace Engine {
	void Print()
	{
		printf("Welcome to the Engine!\n");
	}

	void* LoadObjFile(std::string filePath)
	{
		ObjLoader* objLoader = new ObjLoader();
		return objLoader->LoadFile(filePath);;
	}

	void* LoadTextureFile(std::string filePath)
	{
		TextureLoader* texLoader = new TextureLoader();
		return texLoader->LoadFile(filePath);
	}
}