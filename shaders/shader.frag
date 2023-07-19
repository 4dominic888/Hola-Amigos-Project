#version 330 core
out vec4 FragColor;

in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 posicionLuz;
uniform vec3 colorLuz;

uniform sampler2D la_textura;

void main()
{
    //*texture*/
    vec4 textura = texture(la_textura, TextureCoord);


    //*ambiental*/
    float nivel = 0.1;
    vec3 ambiental = nivel * colorLuz;



    //*Diffusa*/
    vec3 normalizado = normalize(Normal);
    vec3 luzdir = normalize(posicionLuz - FragPos);
    float diff = max(dot(normalizado, luzdir), 0.0);
    vec3 difusa = diff * colorLuz;
    


    
    vec3 result = (ambiental + difusa) * textura.rgb;
    if(textura.a < 0.1) discard;
    FragColor = vec4(result, 1.0);
} 