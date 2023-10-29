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

		if (objFile.is_open())
		{
			while (objFile)
			{
				std::getline(objFile, line);
				Split(line, ' ', lineSplitted);

				std::string vertexInfo = lineSplitted[0];

				if (vertexInfo == "v")
				{
					std::array<float, 3> position{ {std::stof(lineSplitted[1]), std::stof(lineSplitted[2]), std::stof(lineSplitted[3])} };
					objData->vertex_position.push_back(position);
				}
				else if (vertexInfo == "vn")
				{
					std::array<float, 2> normal{ std::stof(lineSplitted[1]), std::stof(lineSplitted[2]) };
					objData->vertex_normal.push_back(normal);
				}
				else if (vertexInfo == "vt")
				{
					std::array<float, 2> texture{ std::stof(lineSplitted[1]), std::stof(lineSplitted[2]) };
					objData->vertex_texture.push_back(texture);
				}
				else if (vertexInfo == "f")
				{
					std::vector<std::string> faceIdSplitter;
					Split(lineSplitted[1], '/', faceIdSplitter);
					Split(lineSplitted[2], '/', faceIdSplitter);
					Split(lineSplitted[3], '/', faceIdSplitter);
					Split(lineSplitted[4], '/', faceIdSplitter);
					std::array<unsigned int, 12> face{
						std::stoi(faceIdSplitter[0]), std::stoi(faceIdSplitter[1]), std::stoi(faceIdSplitter[2]),
						std::stoi(faceIdSplitter[3]), std::stoi(faceIdSplitter[4]), std::stoi(faceIdSplitter[5]),
						std::stoi(faceIdSplitter[6]), std::stoi(faceIdSplitter[7]), std::stoi(faceIdSplitter[8]),
						std::stoi(faceIdSplitter[9]), std::stoi(faceIdSplitter[10]), std::stoi(faceIdSplitter[11])
					};
					objData->face.push_back(face);
				}
				else if (vertexInfo == "o")
				{
					if (firstObjectFound)
						break;
					firstObjectFound = true;
				}

				lineSplitted.clear();
			}

			objFile.close();
			return objData;
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
}