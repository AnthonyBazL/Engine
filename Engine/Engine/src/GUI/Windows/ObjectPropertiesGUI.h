#pragma once

#include "../ImGuiWindow.h"
#include "../../../../Engine/src/Meshes/Mesh.h"

namespace Engine
{
	class ObjectPropertiesGUI : public ImGuiWindow
	{
	public:
		ObjectPropertiesGUI();
		~ObjectPropertiesGUI();
		void Render() override;
		void SetObject(Mesh* pMesh);

	private:
		Mesh* _pMesh = nullptr;
		float _eulerRotation[3] = { 0.0f, 0.0f, 0.0f };
		float _worldPosition[3] = { 0.0f, 0.0f, 0.0f };
		float _scale[3] = { 1.0f , 1.0f, 1.0f };
		float _shininess = 1.0f;
	};
}
