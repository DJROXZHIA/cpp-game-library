#version 400 core

in float texture;
in vec2 texCoords;
in vec4 color;
in mat4 proj;
in mat4 view;

uniform sampler2D u_textures[16];

uniform vec2 u_lightPos[20];
uniform float u_lightRadius[20];
uniform vec4 u_lightColor[20];
uniform vec2 u_camPos;
uniform int u_numLights;
uniform float u_ambient;

out vec4 FragColor;

void main()
{
    int textureIndex = int(texture);
    if(texture(u_textures[textureIndex], texCoords).a < 0.1)
        discard;

    vec2 fragPos = gl_FragCoord.xy;
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 1.0);

    for(int i = 0; i < u_numLights; i++)
    {
        vec2 lightPos;
        lightPos.x = u_lightPos[i].x - u_camPos.x;
        lightPos.y = u_lightPos[i].y + u_camPos.y;
        //lightPos = u_lightPos[i];

        float distance = length(fragPos - lightPos);
        float intensity = 1.0 - (distance / u_lightRadius[i]);
        intensity = clamp(intensity, u_ambient, 1.0);

        vec4 fragColor = texture(u_textures[textureIndex], texCoords) * color * u_lightColor[i] * intensity;
        finalColor += fragColor;
    }    

    if(finalColor == vec4(0.0, 0.0, 0.0, 1.0))
		finalColor = texture(u_textures[textureIndex], texCoords) * color * vec4(u_ambient, u_ambient, u_ambient, 1.0);

    FragColor = vec4(finalColor);
}