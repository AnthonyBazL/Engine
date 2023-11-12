#include "TextureLoader.h"

namespace Engine
{
    TextureData* TextureLoader::LoadFile(std::string filePath)
    {
        int width, height, nbChannels;
        TextureData* textureData = new TextureData();
        textureData->data = stbi_load(filePath.c_str(), &width, &height, &nbChannels, 0);
        textureData->width = width;
        textureData->height = height;
        return textureData;
    }
}
