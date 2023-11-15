#pragma once

#include <GLM/ext/vector_float3.hpp>
#include "Component.h"

class Light : public Component
{
private:
	float _range = 1000.0f;
	float _diffuseIntensity = 1.0f;
	float _ambiantIntensity = 0.05f;

public:
	Light(glm::vec3 position);
	float GetRange() { return _range; }
	float GetDiffuseIntensity() { return _diffuseIntensity; }
	float GetAmbiantIntensity() { return _ambiantIntensity; }
	void SetRange(float range) { _range = range; }
	void SetDiffuseIntensity(float intensity) { _diffuseIntensity = intensity; }
	void SetAmbiantIntensity(float intensity) { _ambiantIntensity = intensity; }
};

