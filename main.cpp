#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "include/stb/stb_image.h"


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "include/Shader.hpp"

#define WIDTH 600
#define HEIGH 600


float vertices[] = {
//   X        Y       Z         R     G     B         t1     t2
    0.5f,   0.5f,    0.0f,     1.0f, 0.0f, 0.0f,     1.0f,  1.0f, 
    0.5f,  -0.5f,    0.0f,     0.0f, 1.0f, 0.0f,     1.0f,  0.0f,
   -0.5f,  -0.5f,    0.0f,     0.0f, 0.0f, 1.0f,     0.0f,  0.0f,
   -0.5f,   0.5f,    0.0f,     1.0f, 0.0f, 0.0f,     0.0f,  1.0f 
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

void redimensionar(GLFWwindow* ventana, int ancho, int alto){
    glViewport(0,0, ancho, alto);
}

const char* leerShader(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return nullptr;
    }

    std::string contenido((std::istreambuf_iterator<char>(archivo)),
                          std::istreambuf_iterator<char>());
    
    archivo.close();

    const char* contenidoChar = contenido.c_str();
    return contenidoChar;
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void teclado(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS){
        switch (key) {
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        
        default:
            break;
        }
    }
}

int main(void)
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Capture Errors in the function error_callback */
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGH, "Hola Amigos", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }

    glfwSetKeyCallback(window, teclado); //teclado
    glfwMakeContextCurrent(window); //contexto
    glfwSetFramebufferSizeCallback(window, redimensionar); //redimensionamiento


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  


    //Imprime descripciones
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    //glViewport(0,0, 800,800);




    // VBO VAO EBO //
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Se configura primero el VAO
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    //Shader
    Shader shader = Shader("shaders/shader.vert", "shaders/shader.frag");


    //Texture
    unsigned int texture; // ID
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &texture); //Inicializacion
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture); // vinculación

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //cerca pixeleado
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //lejos borroso miopia

    // Pa la ruta de la IMAGEN
    int witdh, heigh, nrChannels;
    unsigned char* data = stbi_load("img/piedras.jpg", &witdh, &heigh, &nrChannels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, witdh, heigh, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else std::cout<<"Ocurrio un error al cargar la textura"<< std::endl;

    stbi_image_free(data);


    float temp;
    int vertColorID = glGetUniformLocation(shader.ID, "move");


    shader.use();
    glBindVertexArray(VAO);

    /* Loop until the user closes the window */

    glfwSwapInterval(1); //Para evitar lag
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(1.0 , 0.2 ,0.2 , 1.0);
        glClear(GL_COLOR_BUFFER_BIT);



        temp = 0.5 + (  0.3 * sin (glfwGetTime()) );
        glUniform1f(vertColorID, temp);


        glBindTexture(GL_TEXTURE_2D, texture);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.del();

    glfwTerminate();
    return 0;
}