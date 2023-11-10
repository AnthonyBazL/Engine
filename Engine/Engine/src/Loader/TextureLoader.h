#pragma once
#include <string>
#include "stb_image.h"

namespace Engine
{
	class TextureLoader
	{
	public:
		unsigned char* LoadFile(std::string filePath);
	};
}

