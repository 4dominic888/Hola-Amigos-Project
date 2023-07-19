#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Movimiento{
    ADELANTE, // W
    ATRAS,    // S
    DERECHA,  // D
    IZQUIERDA,// A
    ARRIBA,   // SPACE
    ABAJO     // SHIFT
};

class Camara{
    public:
    //camera matrices
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;

    //mouse
        bool firstMouse = true;
        float yawMouse;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
        float pitchMouse;

        float velocityCamera;
        float velocityMouse;

    //funciones
        void tecladoFunc(Movimiento tipo ,float deltatime);
        void mouseFunc(float xoffset, float yoffset);
        Camara( 
            glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f), 
            glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f), 
            float velocityCamera = 2.5f, float velocityMouse = 0.1f, 
            float yawMouse = -90.0f, float pitchMouse = 0.0f);

        glm::mat4 GetVistaMatrix();
};

#endif