#pragma once
#include <string>
#include "stb_image.h"


namespace Engine
{

//#if ENGINE_DLL_BUILD
//#define ENGINE_DLL_STATE __declspec(dllexport)
//#else
//#define ENGINE_DLL_STATE __declspec(dllimport)
//#endif

	/*ENGINE_DLL_STATE*/ struct TextureData
	{
	public:
		unsigned char* data = nullptr;
		int width = 0, height = 0, channels = 0;
	};

	class TextureLoader
	{
	public:
		static TextureData* LoadFile(std::string filePath, int componentsPerPixel);
	};
}

