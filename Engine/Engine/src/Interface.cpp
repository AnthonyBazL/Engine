#include "Interface.h"
#include <stdio.h>

namespace Engine {
	void Print()
	{
		printf("Welcome to the Engine!\n");
	}

	void* LoadFile(std::string filePath)
	{
		ObjLoader* objLoader = new ObjLoader();
		ObjFileData* data = objLoader->LoadFile(filePath);
		return data;
	}
}