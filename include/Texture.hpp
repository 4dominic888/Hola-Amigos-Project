#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb/stb_image.h"
#include "glad/glad.h"

class Texture{
    public:
        unsigned int ID;
        Texture(GLenum type ,const char* filename);
        void bind(GLenum numTexture, GLenum texture);
};

#endif