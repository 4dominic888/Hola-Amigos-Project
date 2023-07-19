#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TextureCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 modelo;
uniform mat4 vista;
uniform mat4 projeccion;


void main(){
    
    FragPos = vec3(modelo * vec4(aPos, 1.0));
    Normal = aNormal;
    TextureCoord = aTextureCoord;

    gl_Position = projeccion * vista  * vec4(FragPos, 1.0);
}