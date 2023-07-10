#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 TextureCoord;

uniform sampler2D la_textura;

void main()
{
    vec4 textura =texture(la_textura, TextureCoord);
    if(textura.a < 0.1) discard;
    FragColor = textura;
} 