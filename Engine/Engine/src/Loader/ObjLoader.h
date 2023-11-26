#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <array>
#include <algorithm>

namespace Engine
{
#if ENGINE_DLL_BUILD
#define ENGINE_DLL_STATE __declspec(dllexport)
#else
#define ENGINE_DLL_STATE __declspec(dllimport)
#endif

	ENGINE_DLL_STATE struct ObjectInformations
	{
	public:
		std::vector<std::array<float, 3>> positions;	// v 1.0 0.0 0.0 
		std::vector<std::array<float, 3>> normals;	// vn 0.0 1.0 0.0
		std::vector<std::array<float, 2>> uvs;	// vt 1.0 0.0
		std::vector<std::array<unsigned int, 12>> face;		// f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 (index start at 1, not 0)
		std::vector<float> positions_sorted; // Sort positions to use them with rendering API (OpenGL)
		std::vector<float> uvs_sorted; // Sort uvs to use them with rendering API (OpenGL)
		std::vector<float> normals_sorted; // Sort uvs to use them with rendering API (OpenGL)
	};

	ENGINE_DLL_STATE struct ObjFileData
	{
	public:
		std::vector<ObjectInformations*> objects;
		bool face_triangle = true;
	};

	class ObjLoader
	{
	private:
		enum FaceType { TRIANGLE = 0, QUAD = 1 };

		static void Split(std::string const& str, const char delim, std::vector<std::string>& out);
		static void SortVertices(ObjFileData* objFileData);
	public:
		static ObjFileData* LoadFile(std::string filePath);
	};
}