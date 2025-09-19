#version 400 core

in float texture;
in vec2 texCoords;
in vec4 color;

uniform sampler2D u_textures[16];

out vec4 FragColor;

void main()
{
    int textureIndex = int(texture);
    if(texture(u_textures[textureIndex], texCoords).a < 0.1)
        discard;

    vec4 _color = texture(u_textures[textureIndex], texCoords) * color;
    FragColor = vec4(_color.xyz * 0.1, 1.0);
    //FragColor = vec4(_color);
}