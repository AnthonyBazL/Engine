#include "ObjLoader.h"

namespace Engine
{
	ObjFileData* ObjLoader::LoadFile(std::string filePath)
	{
		std::ifstream objFile;
		try
		{
			objFile.open(filePath);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::string line;
		std::vector<std::string> lineSplitted;

		// TODO: This boolean will disappear as soon as current code will support multiple object from an OBJ file
		bool firstObjectFound = false;
		ObjFileData* objData = new ObjFileData();
		FaceType faceType = TRIANGLE;
		bool faceTypeDefined = false;
		int objIndex = -1;

		if (objFile.is_open())
		{
			while (objFile)
			{
				std::getline(objFile, line);
				if (objFile.eof())
				{
					objFile.close();
					SortVertices(objData);
					return objData;
				}

				Split(line, ' ', lineSplitted);

				std::string vertexInfo = lineSplitted[0];

				if (vertexInfo == "v")
				{
					std::array<float, 3> position{ {std::stof(lineSplitted[1]), std::stof(lineSplitted[2]), std::stof(lineSplitted[3])} };
					objData->objects[objIndex]->positions.push_back(position);
				}
				else if (vertexInfo == "vn")
				{
					std::array<float, 3> normal{ std::stof(lineSplitted[1]), std::stof(lineSplitted[2]), std::stof(lineSplitted[3]) };
					objData->objects[objIndex]->normals.push_back(normal);
				}
				else if (vertexInfo == "vt")
				{
					std::array<float, 2> texture{ std::stof(lineSplitted[1]), std::stof(lineSplitted[2]) };
					objData->objects[objIndex]->uvs.push_back(texture);
				}
				else if (vertexInfo == "f")
				{
					if (!faceTypeDefined && lineSplitted.size() == 5)
					{
						faceType = QUAD;
						objData->face_triangle = false;
					}
					faceTypeDefined = true;

					std::vector<std::string> faceIdSplitter;
					std::array<unsigned int, 12> face;

					// TODO: Check for a clean way collect face datas
					// TODO: Be able to manage triangle and quad faces in the same object
					if (faceType == QUAD)
					{
						// TODO: In quad face case, be able to triangulate. Need to be careful on UVs and normals also.
						Split(lineSplitted[1], '/', faceIdSplitter);
						Split(lineSplitted[2], '/', faceIdSplitter);
						Split(lineSplitted[3], '/', faceIdSplitter);
						Split(lineSplitted[4], '/', faceIdSplitter);
						
						face = {
							std::stoul(faceIdSplitter[0]), faceIdSplitter[1].empty() ? 0 : std::stoul(faceIdSplitter[1]), std::stoul(faceIdSplitter[2]),
							std::stoul(faceIdSplitter[3]), faceIdSplitter[4].empty() ? 0 : std::stoul(faceIdSplitter[4]), std::stoul(faceIdSplitter[5]),
							std::stoul(faceIdSplitter[6]), faceIdSplitter[7].empty() ? 0 : std::stoul(faceIdSplitter[7]), std::stoul(faceIdSplitter[8]),
							std::stoul(faceIdSplitter[9]), faceIdSplitter[10].empty() ? 0 : std::stoul(faceIdSplitter[10]), std::stoul(faceIdSplitter[11])
						};
					}
					else if (faceType == TRIANGLE)
					{
						Split(lineSplitted[1], '/', faceIdSplitter);
						Split(lineSplitted[2], '/', faceIdSplitter);
						Split(lineSplitted[3], '/', faceIdSplitter);
						face = {
							std::stoul(faceIdSplitter[0]), std::stoul(faceIdSplitter[1]), std::stoul(faceIdSplitter[2]),
							std::stoul(faceIdSplitter[3]), std::stoul(faceIdSplitter[4]), std::stoul(faceIdSplitter[5]),
							std::stoul(faceIdSplitter[6]), std::stoul(faceIdSplitter[7]), std::stoul(faceIdSplitter[8])
						};
					}

					objData->objects[objIndex]->face.push_back(face);
				}
				else if (vertexInfo == "o")
				{
					objData->objects.push_back(new ObjectInformations());
					++objIndex;
				}

				lineSplitted.clear();
			}
		}
		else
		{
			std::cout << "Couldn't open file\n";
			return nullptr;
		}

		return nullptr;
	}

	void ObjLoader::Split(std::string const& str, const char delim, std::vector<std::string>& out)
	{
		std::stringstream ss(str);

		std::string s;
		while (std::getline(ss, s, delim)) {
			out.push_back(s);
		}
	}

	void ObjLoader::SortVertices(ObjFileData* objFileData)
	{
		int offsetPositionIndex = 0;
		int offsetUVIndex = 0;
		int offsetNormalIndex = 0;

		for (int objectIndex = 0; objectIndex < objFileData->objects.size(); ++objectIndex)
		{
			for (std::array<unsigned int, 12> faceInfos : objFileData->objects[objectIndex]->face)
			{
				int* vertexPositionsOfFace;
				int* vertexUVsOfFace;
				int* vertexNormalsOfFace;
				if (objFileData->face_triangle)
				{
					vertexPositionsOfFace = new int[]{ (int)faceInfos[0], (int)faceInfos[3], (int)faceInfos[6]};
					vertexUVsOfFace = new int[]{ (int)faceInfos[1], (int)faceInfos[4], (int)faceInfos[7]};
					vertexNormalsOfFace = new int[]{ (int)faceInfos[2], (int)faceInfos[5], (int)faceInfos[8]};
				}
				else
				{
					vertexPositionsOfFace = new int[]{ (int)faceInfos[0], (int)faceInfos[3], (int)faceInfos[6], (int)faceInfos[9]};
					vertexUVsOfFace = new int[]{ (int)faceInfos[1], (int)faceInfos[4], (int)faceInfos[7], (int)faceInfos[10]};
					vertexNormalsOfFace = new int[]{ (int)faceInfos[2], (int)faceInfos[5], (int)faceInfos[8], (int)faceInfos[11]};
				}

				for (int i = 0; i < (objFileData->face_triangle ? 3 : 4); ++i)
				{
					std::array<float, 3> vertexPos = objFileData->objects[objectIndex]->positions[vertexPositionsOfFace[i] - offsetPositionIndex - 1];
					std::array<float, 2> vertexUV = objFileData->objects[objectIndex]->uvs[vertexUVsOfFace[i] - offsetUVIndex - 1];
					std::array<float, 3> vertexNormal = objFileData->objects[objectIndex]->normals[vertexNormalsOfFace[i] - offsetNormalIndex - 1];
					objFileData->objects[objectIndex]->positions_sorted.push_back(vertexPos[0]);
					objFileData->objects[objectIndex]->positions_sorted.push_back(vertexPos[1]);
					objFileData->objects[objectIndex]->positions_sorted.push_back(vertexPos[2]);
					objFileData->objects[objectIndex]->uvs_sorted.push_back(vertexUV[0]);
					objFileData->objects[objectIndex]->uvs_sorted.push_back(vertexUV[1]);
					objFileData->objects[objectIndex]->normals_sorted.push_back(vertexNormal[0]);
					objFileData->objects[objectIndex]->normals_sorted.push_back(vertexNormal[1]);
					objFileData->objects[objectIndex]->normals_sorted.push_back(vertexNormal[2]);
				}
			}

			offsetPositionIndex += objFileData->objects[objectIndex]->positions.size();
			offsetUVIndex += objFileData->objects[objectIndex]->uvs.size();
			offsetNormalIndex += objFileData->objects[objectIndex]->normals.size();
		}
	}
}