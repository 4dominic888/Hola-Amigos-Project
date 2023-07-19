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
#include <windows.h>
#include <mmsystem.h>
#include <random>

//Include creados
#include "include/Shader.hpp"
#include "include/Texture.hpp"
#include "include/Camara.hpp"

using namespace glm;

#define WIDTH 600
#define HEIGH 600

float vertices[] = {
//    X      Y      Z        T1    T2          Normal
    -0.5f, -0.5f,  0.0f,    0.0f, 0.0f,   0.0f, 0.0f,  1.0f,
     0.5f, -0.5f,  0.0f,    1.0f, 0.0f,   0.0f, 0.0f,  1.0f,
     0.5f,  0.5f,  0.0f,    1.0f, 1.0f,   0.0f, 0.0f,  1.0f,
    -0.5f,  0.5f,  0.0f,    0.0f, 1.0f,   0.0f, 0.0f,  1.0f
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2, 
    2, 3, 0
};

float pyramidVertices[] = {
//    x       y        z
   -0.5f,   0.0f,   -0.5f,
    0.5f,   0.0f,   -0.5f,
   -0.5f,   0.0f,    0.5f,
    0.5f,   0.0f,    0.5f,
    0.0f,   1.0f,    0.0f
};

unsigned int pyramidIndices[] = {
    0, 1, 2,
    1, 2, 3,
    0, 1, 4,
    0, 2, 4,
    2, 3, 4,
    3, 1, 4
};


//Camara variables
Camara camara = Camara(vec3(0.0f, 0.0f, 2.0f));
float lastX =  (float)WIDTH / 2.0;
float lastY =  (float)HEIGH / 2.0;

bool firstMouse = true;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float randomInRange(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

void redimensionar(GLFWwindow* ventana, int ancho, int alto) { glViewport(0,0, ancho, alto); }
void error_callback(int error, const char* description) { fprintf(stderr, "Error: %s\n", description); }

void mouse(GLFWwindow* window, double xposIn, double yposIn){
    float xpos = xposIn;
    float ypos = yposIn;

    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camara.mouseFunc(xoffset, yoffset);
}

void teclado(GLFWwindow* window)
{   
    //WASD

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camara.tecladoFunc(ADELANTE, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camara.tecladoFunc(IZQUIERDA, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camara.tecladoFunc(ATRAS, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camara.tecladoFunc(DERECHA, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camara.tecladoFunc(ARRIBA, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camara.tecladoFunc(ABAJO, deltaTime);

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);

}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Capture Errors in the function error_callback */
    glfwSetErrorCallback(error_callback);

    /* Establecer minimo y maximo la version de OpenGL utilizable */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGH, "Hola Amigos", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }


    glfwMakeContextCurrent(window); //contexto
    glfwSetFramebufferSizeCallback(window, redimensionar); //redimensionamiento
    glfwSetCursorPosCallback(window, mouse); //pal mousse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //mouse config

    sndPlaySound("img/freebird.wav", SND_ASYNC | SND_FILENAME | SND_LOOP);

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
    printf("Con las teclas WASD te mueves\ncon space y shift te mueves verticalmente\ncon el mouse giras\nes como el minecraft\n");



    glEnable(GL_DEPTH_TEST); //para que exista profundidad



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

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(sizeof(float) * 5));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Pyramid Mesh?
    unsigned int pyVBO, pyVAO, pyEBO;
    glGenVertexArrays(1, &pyVAO);
    glGenBuffers(1, &pyVBO);
    glGenBuffers(1, &pyEBO);

    glBindVertexArray(pyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramidIndices), pyramidIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    Shader shader = Shader("shaders/shader.vert", "shaders/shader.frag");
    Shader lightShader = Shader("shaders/light.vert", "shaders/light.frag");
    Texture textura = Texture(GL_TEXTURE_2D ,"img/cucaracha.png");


    //luces
    vec3 posicionLuz = vec3(0.0f, 0.0f, 2.0f);
    vec3 colorLuz = vec3(1.0f, 1.0f, 1.0f);

    vec3 ambiental = colorLuz * vec3(0.6f);
    vec3 difuso = colorLuz * vec3(0.1f);

    //vec3 luzDifusa;

    //modelo projeccion vista
    mat4 vista;
    mat4 modelo;
    mat4 pymodelo;
    mat4 projeccion = perspective(radians(45.0f), (float)(WIDTH) / (float)(HEIGH), 0.1f, 100.0f);

    //shader usado
    float randomAngleX = randomInRange(0.0f, 360.0f);
    float randomAngleY = randomInRange(0.0f, 360.0f);
    float randomAngleZ = randomInRange(0.0f, 360.0f);

    glUniform1i(glGetUniformLocation(shader.ID, "la_textura"), 0);

    float velocidad = 100;
    float currentFrame;
    int frame;

    /* Loop until the user closes the window */
    glfwSwapInterval(1); //Para evitar lag
    while (!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        frame++;

        teclado(window);

        /* Render here */
        glClearColor(0.18, 0.19, 0.21, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //igual profundidad

        if(frame > 800) velocidad = 800;
        if(frame > 1170) velocidad = 1600;
        if(frame > 1780) {velocidad = 100; return 0;}

        shader.use();
        vista = camara.GetVistaMatrix();
        shader.setMat4("projeccion", projeccion);
        shader.setMat4("vista", vista);


        shader.setVec3("luz.posicion", posicionLuz);
        shader.setVec3("posicionVista", camara.Position);

        shader.setVec3("luz.ambiental", ambiental);
        shader.setVec3("luz.difusa", difuso);
        shader.setVec3("luz.especular", 0.5f, 0.5f, 0.5f);

        shader.setVec3("material.ambiental", 1.0f, 1.0f, 1.0f);
        shader.setVec3("material.difusa", 1.0f, 0.82f, 0.82f);
        shader.setVec3("material.especular", 0.73f, 0.72f, 0.74f);

        shader.setfloat("material.brillo", 0.3f);
        
        modelo = mat4(1.0f);
        modelo = rotate(modelo, radians((float)glfwGetTime()*velocidad), vec3(1.0, 0.0, 0.0));
        modelo = rotate(modelo, radians((float)glfwGetTime()*velocidad), vec3(0.0, 1.0, 0.0));
        modelo = rotate(modelo, radians((float)glfwGetTime()*velocidad), vec3(0.0, 0.0, 1.0));
        shader.setMat4("modelo", modelo);
        textura.bind(GL_TEXTURE0 ,GL_TEXTURE_2D); 
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



        //foco
        lightShader.use();
        pymodelo = mat4(1.0f);

        lightShader.setVec3("colorLuz", colorLuz);

        //lightShader.setMat4("projeccion", projeccion);
        //lightShader.setMat4("vista", vista);
        //pymodelo = translate(pymodelo, posicionLuz);
        //lightShader.setMat4("modelo", pymodelo);
        
        //glBindVertexArray(pyVAO);
        //glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        //glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteVertexArrays(1, &pyVAO);
    glDeleteBuffers(1, &pyVBO);
    glDeleteBuffers(1, &pyEBO);

    shader.del();
    lightShader.del();

    glfwTerminate();
    return 0;
}