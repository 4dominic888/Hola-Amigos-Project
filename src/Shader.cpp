#include "../include/Shader.hpp"

Shader::Shader(const std::string& vertex_file, const std::string& fragment_file){

    char log[512];
    int sucess;

    const char* codeVertex = leerShader(vertex_file);
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &codeVertex, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
    if(!sucess){
        glGetShaderInfoLog(vertexShader, 512, NULL, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED!!\n" << log << std::endl;
    }


    const char* codeFragment = leerShader(fragment_file);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &codeFragment, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
    if(!sucess){
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILE!\n" << log << std::endl;
    }

    this->ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &sucess);

    if(!sucess){
        glGetShaderInfoLog(ID, 512, NULL, log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

const char* Shader::leerShader(const std::string& rutaArchivo){
    std::ifstream archivo(rutaArchivo);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo..." << std::endl;
        return nullptr;
    }

    std::string contenido((std::istreambuf_iterator<char>(archivo)),
                          std::istreambuf_iterator<char>());
    
    archivo.close();

    const char* contenidoChar = contenido.c_str();
    return contenidoChar;
}

void Shader::setMat4(const std::string &name, glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec4(const std::string &name, glm::vec4 &vec) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setVec3(const std::string &name, glm::vec3 &vec) const{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::del(){
    glDeleteProgram(ID);
}