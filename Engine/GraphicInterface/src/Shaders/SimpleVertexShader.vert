#version 330 core

layout(location = 0) in vec3 vertexPosition_modelSpace;
layout (location = 1) in vec3 color;

out vec3 fragColor;

void main()
{
	gl_Position.xyz = vertexPosition_modelSpace;
	gl_Position.w = 1.0;
	fragColor = color;
}