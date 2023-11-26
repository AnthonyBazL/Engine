#pragma once

#include "Component.h"

namespace Engine
{
	class Light : public Component
	{
	private:
		float _range = 1000.0f;
		float _diffuseIntensity = 1.0f;
		float _ambiantIntensity = 0.4f;
		float _specularIntensity = 10.0f;

	public:
		Light(float* position);
		float GetRange() { return _range; }
		float GetDiffuseIntensity() { return _diffuseIntensity; }
		float GetAmbiantIntensity() { return _ambiantIntensity; }
		float GetSpecularIntensity() { return _specularIntensity; }
		void SetRange(float range) { _range = range; }
		void SetDiffuseIntensity(float intensity) { _diffuseIntensity = intensity; }
		void SetAmbiantIntensity(float intensity) { _ambiantIntensity = intensity; }
		void SetSpecularIntensity(float intensity) { _specularIntensity = intensity; }
	};
}