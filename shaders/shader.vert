#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoord;


out vec3 color;
out vec2 TextureCoord;

uniform mat4 transformacion;

void main(){
    gl_Position = transformacion * vec4(aPos, 1.0);
    color = aColor;
    TextureCoord = aTextureCoord;
}