#version 330 core

layout(location = 0) in vec3 vertexPosition_modelSpace;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec2 o_uv;
out vec3 o_vertexPosition;
out vec3 o_vertexNormal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(vertexPosition_modelSpace, 1);
	o_uv = uv;
	o_vertexPosition = vec3(u_model * vec4(vertexPosition_modelSpace, 1.0));
	// Convert normal to world space instead of model space
	o_vertexNormal = mat3(transpose(inverse(u_model))) * normal;
}