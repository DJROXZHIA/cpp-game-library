#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float aTexture;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;

out float texture;
out vec2 texCoords;
out vec4 color;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
    texture = aTexture;
    texCoords = aTexCoords;
    color = aColor;
    gl_Position = u_projection * u_view * vec4(aPos, 1.0);
}