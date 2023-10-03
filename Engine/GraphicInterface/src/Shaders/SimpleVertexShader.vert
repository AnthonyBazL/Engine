#version 330 core

layout(location = 0) in vec3 vertexPosition_modelSpace;
layout (location = 1) in vec3 color;

out vec3 fragColor;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vertexPosition_modelSpace, 1);
	fragColor = color;
}