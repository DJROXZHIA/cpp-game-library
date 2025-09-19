#version 400 core

in float texture;
in vec2 texCoords;
in vec4 color;

uniform sampler2D u_textures[16];

out vec4 FragColor;

void main()
{
    int textureIndex = int(texture);
    vec4 _color = texture(u_textures[textureIndex], texCoords) * color;
    _color.a = min(_color.a, 0.4);
    FragColor = vec4(_color);
}