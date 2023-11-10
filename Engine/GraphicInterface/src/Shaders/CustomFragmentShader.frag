#version 330 core

in vec2 out_uv;

out vec3 color;
uniform sampler2D ourTexture;

void main()
{
    // Flip vertical as OpenGL don't load texture the same way as texture loader store data in memory
    // OpenGL: left to right, bottom to top
    // Texture Loader: left to right, top to bottom
    color = texture(ourTexture, vec2(out_uv.x, out_uv.y * -1.0)).rgb;
}