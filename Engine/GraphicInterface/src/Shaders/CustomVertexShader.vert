#version 330 core

layout(location = 0) in vec3 vertexPosition_modelSpace;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec2 o_uv;
out vec3 o_vertexPosition;
out vec3 o_vertexNormal;
out vec3 o_lightPosition;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform vec3 u_lightPosition;

void main()
{
	gl_Position = MVP * vec4(vertexPosition_modelSpace, 1);
	o_uv = uv;
	o_vertexPosition = vertexPosition_modelSpace;
	o_vertexNormal = normal;
	o_lightPosition = (MVP * vec4(u_lightPosition, 1)).xyz;
}