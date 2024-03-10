#include "TextureLoader.h"

namespace Engine
{
    TextureData* TextureLoader::LoadFile(std::string filePath, int componentsPerPixel = 0)
    {
        int width = 0, height = 0, nbChannels = 0;
        TextureData* textureData = new TextureData();
        textureData->data = stbi_load(filePath.c_str(), &width, &height, &nbChannels, componentsPerPixel);
        textureData->width = width;
        textureData->height = height;
        textureData->channels = nbChannels;
        return textureData;
    }
}
