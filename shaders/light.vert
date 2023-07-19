#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 modelo;
uniform mat4 vista;
uniform mat4 projeccion;

void main(){
    gl_Position = projeccion * vista * modelo * vec4(aPos, 1.0);
}