#include "Scene.h"

namespace Engine
{
	Scene::Scene()
	{
		_pCamera = new Camera(_cameraPosition);
		_pLight = new Light(_lightPosition);
		_meshes.push_back(new Triangle(_pCamera, _pLight, _firstTrianglePosition));
		_meshes.push_back(new Triangle(_pCamera, _pLight, _secondTrianglePosition));
		_meshes.push_back(new CustomMesh(_pCamera, _pLight, _customMeshPosition,
			"C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\obj\\Sphere.obj", // Obj
			{ "C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\textures\\rock.jpg" }, // Textures
			"src/Shaders/CustomVertexShader.vert", "src/Shaders/CustomFragmentShader.frag")); // Shaders

		//_meshes.push_back(new CustomMesh(_pCamera, _pLight, glm::vec3(0.0f),
		//	"C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\obj\\MultipleObject.obj", // Obj
		//	{ "C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\textures\\test.jpg",
		//	"C:\\Users\\abaze\\Documents\\C++ Projects\\Engine\\Engine\\GraphicInterface\\resources\\textures\\suzanne.jpg" }, // Textures
		//	"src/Shaders/CustomVertexShader.vert", "src/Shaders/CustomFragmentShader.frag")); // Shaders	
	}

	Scene::~Scene()
	{
	}
}
