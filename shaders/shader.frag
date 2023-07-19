#version 330 core
out vec4 FragColor;


struct Material{
    vec3 ambiental;
    vec3 difusa;
    vec3 especular;
    float brillo;
};

struct Luz{
    vec3 posicion;
    vec3 ambiental;
    vec3 difusa;
    vec3 especular;
};

in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragPos;


uniform vec3 posicionVista;
uniform Material material;
uniform Luz luz;

uniform sampler2D la_textura;

void main()
{
    //*texture*/
    vec4 textura = texture(la_textura, TextureCoord);


    //*ambiental*/
    vec3 ambiental = luz.ambiental * material.ambiental;



    //*Diffusa*/
    vec3 normalizado = normalize(Normal);
    vec3 luzdir = normalize(luz.posicion - FragPos);
    float diff = max(dot(normalizado, luzdir), 0.0);
    vec3 difusa = luz.difusa * (diff * material.difusa);
    

    //*Especular*/
    float nivelEspecular = 0.5;
    vec3 vistaDir = normalize(posicionVista - FragPos);
    vec3 reflectacionDir = reflect(-luzdir, normalizado);
    float spec = pow(max(dot(vistaDir, reflectacionDir), 0.0), material.brillo * 128);
    vec3 especular = luz.especular * (spec * material.especular);




    vec3 result = (ambiental + difusa + especular) * textura.rgb;
    if(textura.a < 0.1) discard;
    FragColor = vec4(result, 1.0);
} 