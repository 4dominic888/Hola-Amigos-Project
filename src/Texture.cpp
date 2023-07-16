#include "../include/Texture.hpp"
#include <iostream>


Texture::Texture(GLenum type ,const char* filename){
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &ID); //Inicializacio
    glBindTexture(type, ID); // vinculación

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //cerca pixeleado
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //lejos borroso miopia asdasd


    // Pa la ruta de la IMAGEN
    int witdh, heigh, nrChannels;
    unsigned char* data = stbi_load(filename, &witdh, &heigh, &nrChannels, 0);

    if(data){
        glTexImage2D(type, 0, GL_RGBA, witdh, heigh, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(type);
    }
    else std::cout<<"Ocurrio un error al cargar la textura, revise el codigo"<< std::endl;

    stbi_image_free(data);
}

void Texture::bind(GLenum texture){
    glActiveTexture(texture);
    glBindTexture(texture, ID);
}