#version 330 core

in vec2 o_uv;
in vec3 o_vertexPosition;
in vec3 o_vertexNormal;
in vec3 o_lightPosition;

uniform sampler2D u_texture;
uniform float u_diffuseLightIntensity;
uniform float u_ambiantLightIntensity;

out vec3 color;


void main()
{
    // Specular light
    vec3 light_vector = normalize(o_lightPosition - o_vertexPosition);
    float cos_angle = dot(light_vector, o_vertexNormal);
    float diffuse_light = clamp(cos_angle, 0.0, 1.0) * u_diffuseLightIntensity;

    // Flip vertical as OpenGL don't load texture the same way as texture loader store data in memory
    // OpenGL: left to right, bottom to top
    // Texture Loader: left to right, top to bottom
    vec3 baseColor = texture(u_texture, vec2(o_uv.x, o_uv.y * -1.0)).rgb;

    // Apply diffuse and ambiant light
    color = baseColor * diffuse_light + vec3(u_ambiantLightIntensity);
}