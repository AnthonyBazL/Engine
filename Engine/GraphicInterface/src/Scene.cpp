#include "Scene.h"

Scene::Scene()
{
	_pCamera = new Camera(glm::vec3(0.0f, 0.0f, -10));
	_pLight = new Light(glm::vec3(-10.0f, 10.0f, 0.0f));
	_meshes.push_back(new Triangle(_pCamera, _pLight, glm::vec3(0.0f)));
	_meshes.push_back(new Triangle(_pCamera, _pLight, glm::vec3(1.5f, 0.0f, 0.0f)));
	_meshes.push_back(new CustomMesh(_pCamera, _pLight, glm::vec3(0.0f), 
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
