#version 330 core

in vec2 o_uv;
in vec3 o_vertexPosition;
in vec3 o_vertexNormal;

uniform sampler2D u_texture;
uniform float u_diffuseLightIntensity;
uniform float u_specularLightIntensity;
uniform float u_ambiantLightIntensity;
uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;
uniform float u_shininess;

out vec3 color;


void main()
{
    vec3 normal = normalize(o_vertexNormal);
    vec3 lightColor = vec3(1.0, 1.0 ,1.0);

    // Ambiant light
    vec3 ambiant_light = vec3(u_ambiantLightIntensity);

    // Diffuse light
    vec3 light_vector = normalize(u_lightPosition - o_vertexPosition);
    float cos_angle = dot(normal, light_vector);
    vec3 diffuse_light = max(cos_angle, 0.0) * lightColor * u_diffuseLightIntensity;

    // Specular light
    vec3 camera_vector = normalize(u_cameraPosition - o_vertexPosition);
    vec3 reflectedLight_vector = reflect(-light_vector, normal);
    cos_angle = dot(camera_vector, reflectedLight_vector);
    vec3 specular_light = pow(max(cos_angle, 0.0), u_shininess) * u_specularLightIntensity * lightColor;

    // Flip vertical as OpenGL don't load texture the same way as texture loader store data in memory
    // OpenGL: left to right, bottom to top
    // Texture Loader: left to right, top to bottom
    vec3 baseColor = texture(u_texture, vec2(o_uv.x, o_uv.y * -1.0)).rgb;

    // Apply diffuse and ambiant light
    color = baseColor * (diffuse_light + specular_light + ambiant_light);
}