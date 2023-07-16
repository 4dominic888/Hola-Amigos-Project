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
//    X       Y     Z       t1   t2
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    /*
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    */
};

vec3 cubePositions[] = {
    vec3( 0.0f,  0.0f,  0.0f),
    vec3( 2.0f,  5.0f, -15.0f),
    vec3(-1.5f, -2.2f, -2.5f),
    vec3(-3.8f, -2.0f, -12.3f),
    vec3( 2.4f, -0.4f, -3.5f),
    vec3(-1.7f,  3.0f, -7.5f),
    vec3( 1.3f, -2.0f, -2.5f),
    vec3( 1.5f,  2.0f, -2.5f),
    vec3( 1.5f,  0.2f, -1.5f),
    vec3(-1.3f,  1.0f, -1.5f)
};

//mouse
bool firstMouse = true;
float yawMouse   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitchMouse =  0.0f;
float lastX =  (float)WIDTH / 2.0;
float lastY =  (float)HEIGH / 2.0;
float fov   =  45.0f;

//camera
vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

//time
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

/*
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};
*/

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

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yawMouse += xoffset;
    pitchMouse += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitchMouse > 89.0f)
        pitchMouse = 89.0f;
    if (pitchMouse < -89.0f)
        pitchMouse = -89.0f;


    vec3 front;
    front.x = cos(radians(yawMouse)) * cos(radians(pitchMouse));
    front.y = sin(radians(pitchMouse));
    front.z = sin(radians(yawMouse)) * cos(radians(pitchMouse));
    cameraFront = normalize(front);
}

void scroll(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

static void teclado(GLFWwindow* window)
{   
    float cameraSpeed = 2.5 * deltaTime;
    
    //WASD
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) cameraPos.y += cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) cameraPos.y -= cameraSpeed;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);

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

    glfwMakeContextCurrent(window); //contexto
    glfwSetFramebufferSizeCallback(window, redimensionar); //redimensionamiento
    glfwSetCursorPosCallback(window, mouse); //pal mousse
    glfwSetScrollCallback(window, scroll);// pa la ruedita

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


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
    printf("Con las teclas WASD te mueves\ncon space y shift te mueves verticalmente\ncon el mouse giras\nes como el minecraft");

    glEnable(GL_DEPTH_TEST); //para que exista profundidad


    // VBO VAO EBO //
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    //Se configura primero el VAO
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(sizeof(float) * 3));
    //glEnableVertexAttribArray(1);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    Shader shader = Shader("shaders/shader.vert", "shaders/shader.frag");
    Texture textura = Texture(GL_TEXTURE_2D ,"img/cucaracha.png");



    //modelo projeccion vista
    mat4 vista;
    mat4 modelo;
    mat4 projeccion = perspective(radians(45.0f), (float)(WIDTH) / (float)(HEIGH), 0.1f, 100.0f);

    //shader usado
    shader.use();
    shader.setMat4("projeccion", projeccion);
    vec4 rainbow = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    /* Loop until the user closes the window */
    glfwSwapInterval(1); //Para evitar lag
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        teclado(window);

        /* Render here */
        glClearColor(0.2 , 0.2 ,0.2 , 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //igual profundidad

        //texture bind
        textura.bind(GL_TEXTURE_2D);   

        //modelos vistas projecciones
        vista = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader.setMat4("vista", vista);
        modelo = mat4(1.0f);
        //dibujar 10 cubos
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 1; i++){
            modelo = rotate(modelo, radians((float)glfwGetTime()*500), vec3(0.0, 1.0, 0.0));
            modelo = translate(modelo, vec3(0,(cos(glfwGetTime()*4))/2,0.5));
            rainbow = vec4(
                (sin((glfwGetTime()*5) + 1.0f)) *0.5f,
                (sin(glfwGetTime() *5 + 2.0f * M_PI/3.0f)+1.0f) *0.5f,
                (sin(glfwGetTime() *5 + 4.0f * M_PI/3.0f)+1.0f) *0.5f,
            
            1.0f);
            shader.setMat4("modelo", modelo);
            shader.setVec4("rain", rainbow);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //dibujado
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    shader.del();

    glfwTerminate();
    return 0;
}