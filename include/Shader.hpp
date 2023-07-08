#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"
#include <fstream>
#include <string>
#include <math.h>
#include <iostream>

class Shader{
    public:
        unsigned int ID;
        Shader(const std::string& vertex_file, const std::string& fragment_file);
        void use();
        void del();
        
    private:
        const char* leerShader(const std::string& rutaArchivo);
};

#endif