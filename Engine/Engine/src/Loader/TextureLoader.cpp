#include "TextureLoader.h"

unsigned char* Engine::TextureLoader::LoadFile(std::string filePath)
{
    int width, height, nbChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nbChannels, 0);
    return data;
}
