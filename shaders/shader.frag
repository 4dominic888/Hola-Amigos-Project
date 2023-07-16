#version 330 core
out vec4 FragColor;

in vec2 TextureCoord;

uniform sampler2D la_textura;
uniform vec4 rain;

void main()
{
    vec4 textura = texture(la_textura, TextureCoord) * rain;
    if(textura.a < 0.1) discard;
    FragColor = textura;
} 