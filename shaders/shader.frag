#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 TextureCoord;

uniform sampler2D la_textura;

void main()
{
    FragColor = texture(la_textura, TextureCoord) * vec4(color, 1.0);
} 