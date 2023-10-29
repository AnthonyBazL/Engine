#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <array>

namespace Engine
{
#if ENGINE_DLL_BUILD
#define ENGINE_DLL_STATE __declspec(dllexport)
#else
#define ENGINE_DLL_STATE __declspec(dllimport)
#endif

	// For now, it will handle only one object from an OBJ file (an OBJ file can handle multiple object)
	ENGINE_DLL_STATE struct ObjFileData
	{
	public:
		std::vector<std::array<float, 3>> vertex_position;	// v 1.0 0.0 0.0 
		std::vector<std::array<float, 2>> vertex_normal;	// vn 0.0 1.0 0.0
		std::vector<std::array<float, 2>> vertex_texture;	// vt 1.0 0.0
		std::vector<std::array<unsigned int, 12>> face;		// f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 (index start at 1, not 0)
	};

	class ObjLoader
	{
	private:
		void Split(std::string const& str, const char delim, std::vector<std::string>& out);
	public:
		ObjFileData* LoadFile(std::string filePath);
	};
}