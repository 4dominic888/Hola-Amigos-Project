//Include principales
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "include/stb/stb_image.h"

//Include complementarios
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Include de fábrica
#include <stdio.h>
#include <iostream>
#include <math.h>

//Include creados
#include "include/Shader.hpp"
#include "include/Texture.hpp"

using namespace glm;

#define WIDTH 600
#define HEIGH 600


float vertices[] = {
//   X        Y       Z         R     G     B         t1     t2
    0.5f,   0.5f,    0.0f,     1.0f, 1.0f, 1.0f,     1.0f,  1.0f, 
    0.5f,  -0.5f,    0.0f,     1.0f, 1.0f, 1.0f,     1.0f,  0.0f,
   -0.5f,  -0.5f,    0.0f,     1.0f, 1.0f, 1.0f,     0.0f,  0.0f,
   -0.5f,   0.5f,    0.0f,     1.0f, 1.0f, 1.0f,     0.0f,  1.0f 
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

void redimensionar(GLFWwindow* ventana, int ancho, int alto) { glViewport(0,0, ancho, alto); }
void error_callback(int error, const char* description) { fprintf(stderr, "Error: %s\n", description); }

static void teclado(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS){
        switch (key) {
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
        default: break;
        }
    }
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Capture Errors in the function error_callback */
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGH, "Hola Amigos", NULL, NULL);
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



    // VBO VAO EBO //
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Se configura primero el VAO
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    Shader shader = Shader("shaders/shader.vert", "shaders/shader.frag");
    Texture textura = Texture(GL_TEXTURE_2D ,"img/cucaracha.png");

    //Transformaciones

    mat4 transformacion = mat4(1.0f); //Matriz de transformación
    //transformacion = translate(transformacion, vec3(0.3f, 0.2f, 0.0f));
    //transformacion = rotate(transformacion, radians(45.0f), vec3(0.0, 0.0, 1.0));
    //transformacion = scale(transformacion, vec3(1.0, 1.0 ,1.0));
    unsigned int move;

    shader.use();
    glBindVertexArray(VAO);

    

    /* Loop until the user closes the window */

    glfwSwapInterval(1); //Para evitar lag
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2 , 0.2 ,0.2 , 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        textura.bind(GL_TEXTURE_2D);
        transformacion = rotate(transformacion, radians(-0.5f), vec3(0.0, 0.0, 1.0));
        glUniformMatrix4fv(move, 1, GL_FALSE, value_ptr(transformacion));
        
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