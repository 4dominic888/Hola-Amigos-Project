#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"
#include <fstream>
#include <string>
#include <math.h>
#include <iostream>
#include <glm/glm.hpp>

class Shader{
    public:
        unsigned int ID;
        Shader(const std::string& vertex_file, const std::string& fragment_file);
        void setMat4(const std::string &name, glm::mat4 &mat) const;
        void setVec4(const std::string &name, glm::vec4 &vec) const;
        void setVec4(const std::string &name, float x, float y, float z, float w) const;
        void setVec3(const std::string &name, glm::vec3 &vec) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setfloat(const std::string &name, float x) const;
        void use();
        void del();
        
    private:
        const char* leerShader(const std::string& rutaArchivo);
};

#endif